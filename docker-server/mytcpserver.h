#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

/**
 * @brief TCP-сервер для обработки запросов клиентов.
 *
 * Обрабатывает команды регистрации, авторизации, решения уравнений,
 * шифрования и дешифрования данных.
 *
 * @author CryptoApp Team
 * @version 1.0
 */
class TcpServer : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор TCP-сервера.
     *
     * Запускает сервер на порту 33333 и начинает прослушивание входящих подключений.
     *
     * @param parent Родительский объект (по умолчанию nullptr)
     */
    explicit TcpServer(QObject* parent = nullptr);

    /**
     * @brief Деструктор TCP-сервера.
     *
     * Закрывает все соединения и освобождает ресурсы.
     */
    ~TcpServer();

private slots:
    /**
     * @brief Обработчик нового подключения клиента.
     *
     * Принимает соединение, добавляет сокет в список и подключает сигналы.
     */
    void handleNewConnection();

    /**
     * @brief Обработчик отключения клиента.
     *
     * Удаляет сокет клиента из списка подключенных.
     *
     * @param socket Указатель на сокет отключившегося клиента
     */
    void handleClientDisconnected(QTcpSocket* socket);

    /**
     * @brief Обработчик получения данных от клиента.
     *
     * Читает команду от клиента и направляет ее в соответствующий обработчик.
     *
     * @param socket Указатель на сокет клиента
     */
    void processClientData(QTcpSocket* socket);

private:
    /**
     * @brief Обрабатывает команду регистрации.
     *
     * Формат команды: "reg login:password"
     *
     * @param socket Сокет клиента
     * @param credentials Строка с логином и паролем
     */
    void processRegistration(QTcpSocket* socket, const QString& credentials);

    /**
     * @brief Обрабатывает команду авторизации.
     *
     * Формат команды: "auth login:password"
     *
     * @param socket Сокет клиента
     * @param arguments Строка с логином и паролем
     */
    void processAuthentication(QTcpSocket* socket, const QString& arguments);

    /**
     * @brief Обрабатывает команду решения уравнения.
     *
     * Формат команды: "equation:func:a:b:epsilon"
     *
     * @param socket Сокет клиента
     * @param arguments Строка с параметрами уравнения
     */
    void processEquation(QTcpSocket* socket, const QString& arguments);

    /**
     * @brief Обрабатывает команду шифрования.
     *
     * Формат команды: "encrypt:текст"
     *
     * @param socket Сокет клиента
     * @param text Текст для шифрования
     */
    void processEncryption(QTcpSocket* socket, const QString& text);

    /**
     * @brief Обрабатывает команду дешифрования.
     *
     * Формат команды: "decrypt:текст"
     *
     * @param socket Сокет клиента
     * @param text Текст для дешифрования
     */
    void processDecryption(QTcpSocket* socket, const QString& text);

    /**
     * @brief Отправляет ответ клиенту.
     *
     * @param socket Сокет клиента
     * @param message Текст ответа
     */
    void sendResponse(QTcpSocket* socket, const QString& message);

    QTcpServer* m_server;                  ///< TCP-сервер
    QList<QTcpSocket*> m_connectedClients; ///< Список подключенных клиентов
};

#endif // MYTCPSERVER_H