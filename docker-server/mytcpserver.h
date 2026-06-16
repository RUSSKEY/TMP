#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QMap>

class TcpServer : public QObject
{
    Q_OBJECT

public:
    explicit TcpServer(QObject* parent = nullptr);
    ~TcpServer();

private slots:
    void handleNewConnection();
    void handleClientDisconnected(QTcpSocket* socket);
    void processClientData(QTcpSocket* socket);

private:
    void processRegistration(QTcpSocket* socket, const QString& credentials);
    void processAuthentication(QTcpSocket* socket, const QString& credentials);
    void processEquation(QTcpSocket* socket, const QString& arguments);
    void processEncryption(QTcpSocket* socket, const QString& text);
    void processDecryption(QTcpSocket* socket, const QString& text);
    void sendResponse(QTcpSocket* socket, const QString& message);

    // Функции админа
    void processAdminListUsers(QTcpSocket* socket);
    void processAdminDeleteUser(QTcpSocket* socket, const QString& username);

    QTcpServer* m_server;
    QList<QTcpSocket*> m_connectedClients;
    QMap<QTcpSocket*, QString> clientLogins;
};

#endif // MYTCPSERVER_H