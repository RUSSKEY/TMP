#pragma once

#include <QtWidgets/QDialog>
#include "mainwindow.h"

namespace Ui {
    class AuthDialog;
}

/**
 * @brief Диалоговое окно авторизации пользователя.
 *
 * Обеспечивает вход пользователя в систему с проверкой логина и пароля.
 * После успешной авторизации открывает главное окно приложения.
 *
 * @author CryptoApp Team
 * @version 1.0
 */
class AuthDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Конструктор диалога авторизации.
     *
     * Устанавливает соединение с сервером, настраивает пользовательский интерфейс
     * и подключает обработчики сигналов.
     *
     * @param parent Указатель на родительский виджет (по умолчанию nullptr)
     */
    explicit AuthDialog(QWidget* parent = nullptr);

    /**
     * @brief Деструктор диалога авторизации.
     */
    ~AuthDialog();

private slots:
    /**
     * @brief Обработчик нажатия кнопки "Войти".
     *
     * Считывает логин и пароль из полей ввода и отправляет
     * команду аутентификации на сервер.
     */
    void on_pushButtonLogin_clicked();

    /**
     * @brief Обработчик нажатия кнопки "Зарегистрироваться".
     *
     * @signal showRegisterRequested Сигнал для открытия окна регистрации
     */
    void on_pushButtonRegister_clicked();

private:
    Ui::AuthDialog* ui;           ///< Указатель на объект пользовательского интерфейса
    MainWindow* mainWindow = nullptr; ///< Указатель на главное окно приложения

signals:
    /**
     * @brief Сигнал запроса на открытие окна регистрации.
     */
    void showRegisterRequested();
};