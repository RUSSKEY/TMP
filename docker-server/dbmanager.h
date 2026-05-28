#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QObject>

/**
 * @brief Менеджер базы данных SQLite.
 *
 * Обеспечивает единую точку доступа к базе данных проекта.
 * Реализует паттерн проектирования Singleton для управления подключением.
 *
 * @author CryptoApp Team
 * @version 1.0
 */
class DatabaseManager
{
public:
    // Запрещаем копирование (для синглтона)
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    /**
     * @brief Возвращает единственный экземпляр менеджера БД.
     *
     * @return DatabaseManager* Указатель на единственный экземпляр
     */
    static DatabaseManager* instance();

    /**
     * @brief Возвращает объект подключения к базе данных.
     *
     * @return QSqlDatabase Объект базы данных SQLite
     */
    QSqlDatabase database() const;

    /**
     * @brief Вычисляет SHA-384 хэш пароля.
     *
     * Используется для безопасного хранения паролей в базе данных.
     *
     * @param password Пароль в открытом виде
     * @return QString Хэш пароля в виде шестнадцатеричной строки
     */
    static QString hashPassword(const QString& password);

private:
    /**
     * @brief Приватный конструктор (для синглтона).
     *
     * Открывает соединение с базой данных и создает необходимые таблицы.
     */
    DatabaseManager();

    /**
     * @brief Деструктор (приватный для синглтона).
     */
    ~DatabaseManager() = default;

    /**
     * @brief Инициализирует базу данных.
     *
     * Включает поддержку внешних ключей и вызывает создание таблиц.
     */
    void initializeDatabase();

    /**
     * @brief Создает необходимые таблицы в базе данных.
     *
     * Создает таблицу users для хранения учетных записей пользователей.
     */
    void createTables();

    static DatabaseManager* m_instance; ///< Статический указатель на единственный экземпляр
    QSqlDatabase m_database;            ///< Объект подключения к базе данных
};

#endif // DATABASEMANAGER_H