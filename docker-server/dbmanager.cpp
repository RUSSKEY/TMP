#include "dbmanager.h"
#include "sha384.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <array>
#include <cstring>

DatabaseManager* DatabaseManager::m_instance = nullptr;

DatabaseManager::DatabaseManager()
{
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName("project_data.db");

    if (!m_database.open()) {
        qCritical() << "Failed to open database:" << m_database.lastError().text();
        return;
    }

    qInfo() << "Database opened successfully";
    initializeDatabase();
}

DatabaseManager* DatabaseManager::instance()
{
    if (!m_instance) {
        m_instance = new DatabaseManager();
    }
    return m_instance;
}

QSqlDatabase DatabaseManager::database() const
{
    return m_database;
}

void DatabaseManager::initializeDatabase()
{
    QSqlQuery query(m_database);

    if (!query.exec("PRAGMA foreign_keys = ON")) {
        qWarning() << "Failed to enable foreign keys:" << query.lastError().text();
    }

    createTables();
}

void DatabaseManager::createTables()
{
    QSqlQuery query(m_database);

    // колонка role, которая по умолчанию равна 'user'
    const QStringList tables = {
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "login TEXT UNIQUE NOT NULL, "
        "password TEXT NOT NULL, "
        "role TEXT NOT NULL DEFAULT 'user')"
    };

    for (const auto& tableSql : tables) {
        if (!query.exec(tableSql)) {
            qCritical() << "Failed to create table:" << query.lastError().text();
        }
    }

    // Автоматическое создание админа в базе данных при первом запуске, если его еще нет
    query.prepare("SELECT id FROM users WHERE login = 'admin'");
    if (query.exec() && !query.next()) {
        query.prepare("INSERT INTO users (login, password, role) VALUES (:login, :password, :role)");
        query.bindValue(":login", "admin");
        query.bindValue(":password", hashPassword("admin"));
        query.bindValue(":role", "admin");
        if (!query.exec()) {
            qCritical() << "Failed to seed admin user:" << query.lastError().text();
        } else {
            qInfo() << "Default admin user created in Database";
        }
    }
}

QString DatabaseManager::hashPassword(const QString& password)
{
    return SHA384::hash(password);
}
