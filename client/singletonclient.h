#pragma once

#include <QtNetwork/QTcpSocket>
#include <QtCore/QObject>

/**
 * @brief Синглтон-клиент для TCP-соединения с сервером.
 *
 * Обеспечивает единую точку доступа к сетевому соединению во всем приложении.
 * Реализует паттерн проектирования Singleton.
 *
 * @author CryptoApp Team
 * @version 1.0
 */
class SingletonClient : public QObject {
    Q_OBJECT

signals:
    /**
     * @brief Сигнал, испускаемый при получении ответа от сервера.
     *
     * @param message Текст ответа от сервера
     */
    void responseReceived(const QString& message);

public:
    /**
     * @brief Возвращает единственный экземпляр класса.
     *
     * @return SingletonClient* Указатель на единственный экземпляр
     */
    static SingletonClient* instance();

    /**
     * @brief Устанавливает соединение с сервером.
     *
     * Подключается к серверу по адресу 127.0.0.1:33333
     */
    void establishConnection();

    /**
     * @brief Отправляет команду на сервер.
     *
     * Форматирует команду с добавлением символов конца строки и отправляет.
     *
     * @param command Текст команды для отправки
     */
    void transmitCommand(const QString& command);

    /**
     * @brief Возвращает указатель на TCP-сокет.
     *
     * @return QTcpSocket* Указатель на объект сокета
     */
    QTcpSocket* socket() const;

    /**
     * @brief Возвращает последний полученный ответ от сервера.
     *
     * @return QString Последний ответ или пустая строка, если ответов не было
     */
    QString latestResponse() const;

private slots:
    /**
     * @brief Обработчик установки соединения.
     *
     * Выводит отладочное сообщение об успешном подключении.
     */
    void connectionEstablished();

    /**
     * @brief Обработчик получения данных от сервера.
     *
     * Читает данные из сокета и испускает сигнал responseReceived.
     */
    void dataAvailable();

    /**
     * @brief Обработчик потери соединения.
     *
     * Выводит отладочное сообщение о разрыве связи.
     */
    void connectionLost();

private:
    /**
     * @brief Приватный конструктор (для синглтона).
     *
     * @param parent Родительский объект (по умолчанию nullptr)
     */
    explicit SingletonClient(QObject* parent = nullptr);

    QTcpSocket* m_socket;               ///< TCP-сокет для связи с сервером
    static SingletonClient* m_instance; ///< Статический указатель на единственный экземпляр
    QString m_lastResponse;             ///< Последний полученный ответ от сервера
};