#include "mytcpserver.h"
#include "dbmanager.h"
#include <QDebug>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlError>
#include <QRegularExpression>
#include <QString>
#include <cmath>
#include <QFile>

TcpServer::TcpServer(QObject* parent) : QObject(parent),
    m_server(new QTcpServer(this))
{
    if (!m_server->listen(QHostAddress::Any, 33333)) {
        qCritical() << "Failed to start server";
    } else {
        qInfo() << "Server started on port 33333";
        connect(m_server, &QTcpServer::newConnection,
                this, &TcpServer::handleNewConnection);
    }
}

TcpServer::~TcpServer()
{
    m_server->close();
    qDeleteAll(m_connectedClients);
}

QMap<QTcpSocket*, QString> clientLogins;

void TcpServer::handleNewConnection()
{
    QTcpSocket* clientSocket = m_server->nextPendingConnection();
    m_connectedClients.append(clientSocket);

    connect(clientSocket, &QTcpSocket::readyRead,
            this, [this, clientSocket]() { processClientData(clientSocket); });
    connect(clientSocket, &QTcpSocket::disconnected,
            this, [this, clientSocket]() { handleClientDisconnected(clientSocket); });

    sendResponse(clientSocket, "Connected to server");
}

void TcpServer::handleClientDisconnected(QTcpSocket* socket)
{
    m_connectedClients.removeAll(socket);
    socket->deleteLater();
    qInfo() << "Client disconnected";
}

void TcpServer::processClientData(QTcpSocket* socket)
{
    QString data = QString::fromUtf8(socket->readAll());
    QStringList commands = data.split(QRegularExpression("[\r\n]+"), Qt::SkipEmptyParts);

    for (const QString& rawCommand : commands) {
        QString command = rawCommand.trimmed();
        if (command.isEmpty()) continue;

        qDebug() << "Processing command:" << command;

        QStringList parts = command.split(" ", Qt::SkipEmptyParts);
        if (parts.isEmpty()) {
            sendResponse(socket, "Error: Empty command");
            continue;
        }

        QString cmd = parts[0].toLower();
        QString args = parts.size() > 1 ? parts.mid(1).join(" ") : "";

        if (cmd == "reg") {
            processRegistration(socket, args);
        }
        else if (cmd == "auth") {
            processAuthentication(socket, args);
        }
        else if (cmd == "equation:") {
            processEquation(socket, args);
        }
        else if (cmd == "encrypt:") {
            processEncryption(socket, args);
        }
        else if (cmd == "decrypt:") {
            processDecryption(socket, args);
        }
        else {
            sendResponse(socket, "Error: Unknown command");
        }
    }
}

void TcpServer::processRegistration(QTcpSocket* socket, const QString& credentials)
{
    const QStringList parts = credentials.split(":");
    if (parts.size() != 2) {
        sendResponse(socket, "Error: Use format 'reg login:password'");
        return;
    }

    const QString login = parts[0].trimmed();
    const QString password = parts[1].trimmed();

    if (login.isEmpty() || password.isEmpty()) {
        sendResponse(socket, "Error: Login and password cannot be empty");
        return;
    }

    if (login.toLower() == "admin") {
        sendResponse(socket, "Error: Access denied to register admin");
        return;
    }

    QString hashedPassword = DatabaseManager::hashPassword(password);
    qDebug() << "[SHA-384] Исходный пароль:" << password << " -> ХЭШ:" << hashedPassword;

    QSqlQuery query(DatabaseManager::instance()->database());
    query.prepare("SELECT id FROM users WHERE login = :login");
    query.bindValue(":login", login);

    if (query.exec() && query.next()) {
        sendResponse(socket, "Error: User already exists");
        return;
    }

    query.prepare("INSERT INTO users (login, password, role) VALUES (:login, :password, 'user')");
    query.bindValue(":login", login);
    query.bindValue(":password", hashedPassword);

    if (query.exec()) {
        sendResponse(socket, "Registration successful");
        qInfo() << "New user registered successfully:" << login;
    } else {
        sendResponse(socket, "Error: Registration failed");
        qWarning() << "Database insert error:" << query.lastError().text();
    }
}

void TcpServer::processAuthentication(QTcpSocket* socket, const QString& arguments)
{
    qDebug() << "Auth arguments:" << arguments;

    QStringList creds = arguments.split(":", Qt::SkipEmptyParts);
    if (creds.size() != 2) {
        sendResponse(socket, "Error: Use format 'auth login:password'");
        return;
    }

    QString login = creds[0].trimmed();
    QString password = creds[1].trimmed();

    if (login.isEmpty() || password.isEmpty()) {
        sendResponse(socket, "Error: Login and password cannot be empty");
        return;
    }

    QString hashedPassword = DatabaseManager::hashPassword(password);
    qDebug() << "[SHA-384] Исходный пароль:" << password << " -> ХЭШ:" << hashedPassword;

    QSqlQuery query(DatabaseManager::instance()->database());
    query.prepare("SELECT password, role FROM users WHERE login = :login");
    query.bindValue(":login", login);

    if (!query.exec()) {
        sendResponse(socket, "Error: Database error");
        return;
    }

    if (!query.next()) {
        sendResponse(socket, "Error: User not found");
        return;
    }

    QString dbPassword = query.value(0).toString();
    QString dbRole = query.value(1).toString();

    if (dbPassword == hashedPassword) {
        clientLogins[socket] = dbRole;

        sendResponse(socket, QString("Authentication successful:%1").arg(dbRole));
        qInfo() << "User authenticated successfully. Login:" << login << "Role:" << dbRole;
    } else {
        sendResponse(socket, "Error: Invalid password");
    }
}

void TcpServer::processEquation(QTcpSocket* socket, const QString& arguments)
{
    qDebug() << "Equation/Admin request received:" << arguments;

    // ФУНКЦИЯ АДМИНА 1: СОРТИРОВКА ПО АЛФАВИТУ
    if (arguments.contains("get_users_sorted", Qt::CaseInsensitive)) {
        if (clientLogins.value(socket) != "admin") {
            sendResponse(socket, "Error: Access denied. Admin rights required.");
            return;
        }

        QSqlQuery query(DatabaseManager::instance()->database());
        query.prepare("SELECT login, role FROM users ORDER BY login ASC");
        if (!query.exec()) {
            sendResponse(socket, "Admin Error: Cannot access database");
            return;
        }

        QStringList userList;
        while (query.next()) {
            userList.append(QString("%1(%2)").arg(query.value(0).toString(), query.value(1).toString()));
        }
        sendResponse(socket, QString("ADMIN_DATA:Sorted users: [ %1 ]").arg(userList.join(", ")));
        return;
    }

    // ФУНКЦИЯ АДМИНА 2: ВЫБОР ПО ПАРАМЕТРАМ / ПОИСК
    if (arguments.startsWith("search_user:", Qt::CaseInsensitive)) {
        if (clientLogins.value(socket) != "admin") {
            sendResponse(socket, "Error: Access denied. Admin rights required.");
            return;
        }

        QString pattern = arguments.split(":")[1].trimmed();
        QSqlQuery query(DatabaseManager::instance()->database());
        query.prepare("SELECT login, role FROM users WHERE login LIKE :pattern");
        query.bindValue(":pattern", "%" + pattern + "%");

        if (!query.exec()) {
            sendResponse(socket, "Admin Error: Search failed");
            return;
        }

        QStringList userList;
        while (query.next()) {
            userList.append(QString("%1(%2)").arg(query.value(0).toString(), query.value(1).toString()));
        }
        sendResponse(socket, QString("ADMIN_DATA:Search result for '%1': [ %2 ]").arg(pattern, userList.join(", ")));
        return;
    }

    // ФУНКЦИЯ АДМИНА 3: УДАЛЕНИЕ
    if (arguments.startsWith("delete:", Qt::CaseInsensitive)) {
        if (clientLogins.value(socket) != "admin") {
            sendResponse(socket, "Error: Access denied. Admin rights required.");
            return;
        }

        QString targetUser = arguments.split(":")[1].trimmed();
        if (targetUser.toLower() == "admin") {
            sendResponse(socket, "Admin Error: Cannot delete main admin!");
            return;
        }

        QSqlQuery query(DatabaseManager::instance()->database());
        query.prepare("DELETE FROM users WHERE login = :login");
        query.bindValue(":login", targetUser);

        if (query.exec() && query.numRowsAffected() > 0) {
            sendResponse(socket, QString("ADMIN_DATA:User '%1' successfully deleted.").arg(targetUser));
        } else {
            sendResponse(socket, "Admin Error: User not found.");
        }
        return;
    }

    // УРАВНЕНИЯ МЕТОДОМ ХОРД
    QString cleaned = arguments;
    QStringList parts = cleaned.replace(" ", "").split(":");

    if (parts.size() < 7) {
        sendResponse(socket, "Equation error: Expected format A:B:C:D:a:b:eps");
        return;
    }

    double A = parts[0].toDouble();
    double B = parts[1].toDouble();
    double C = parts[2].toDouble();
    double D = parts[3].toDouble();
    double a = parts[4].toDouble();
    double b = parts[5].toDouble();
    double eps = parts[6].toDouble();

    double x_prev = a;
    double x_curr = b;
    double x_next = 0;

    auto eval = [A, B, C, D](double x) {
        return A*x*x*x + B*x*x + C*x + D;
    };

    for (int i = 0; i < 100; ++i) {
        double fa = eval(x_prev);
        double fb = eval(x_curr);

        if (std::abs(fb - fa) < 1e-9) break;

        x_next = x_curr - (fb * (x_curr - x_prev)) / (fb - fa);

        if (std::abs(x_next - x_curr) < eps) {
            x_curr = x_next;
            break;
        }
        x_prev = x_curr;
        x_curr = x_next;
    }

    sendResponse(socket, QString("Equation solved. Root found: %1").arg(x_curr));
    qInfo() << "Equation solved dynamically. Result:" << x_curr;
}

void TcpServer::processEncryption(QTcpSocket* socket, const QString& text)
{
    qDebug() << "Encryption request received:" << text;
    sendResponse(socket, "Text encrypted successfully (stub implementation)");
    qInfo() << "Text encrypted for client:" << socket->peerAddress().toString();
}

void TcpServer::processDecryption(QTcpSocket* socket, const QString& text)
{
    qDebug() << "Decryption request received:" << text;
    sendResponse(socket, "Decryption processed (stub implementation)");
    qInfo() << "Decryption processed for client:" << socket->peerAddress().toString();
}

void TcpServer::sendResponse(QTcpSocket* socket, const QString& message)
{
    socket->write(message.toUtf8() + "\r\n");
}