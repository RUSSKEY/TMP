#pragma once

#include <QtWidgets/QDialog>

namespace Ui {
    class RegisterDialog;
}

/**
 * @brief Диалоговое окно регистрации нового пользователя.
 *
 * Позволяет создать новую учетную запись с проверкой уникальности логина.
 * Пароль хэшируется алгоритмом SHA-384 перед отправкой на сервер.
 *
 * @author CryptoApp Team
 * @version 1.0
 */
class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор диалога регистрации.
     *
     * Настраивает пользовательский интерфейс и подключает обработчики сигналов.
     *
     * @param parent Указатель на родительский виджет (по умолчанию nullptr)
     */
    explicit RegisterDialog(QWidget* parent = nullptr);

    /**
     * @brief Деструктор диалога регистрации.
     */
    ~RegisterDialog();

private slots:
    /**
     * @brief Обработчик нажатия кнопки "Зарегистрироваться".
     *
     * Проверяет заполненность полей логина и пароля, затем отправляет
     * команду регистрации на сервер.
     */
    void onRegisterClicked();

    /**
     * @brief Обработчик нажатия кнопки "Назад ко входу".
     *
     * Возвращает пользователя к окну авторизации.
     */
    void handleBackToLogin();

private:
    Ui::RegisterDialog* ui;       ///< Указатель на объект пользовательского интерфейса

signals:
    /**
     * @brief Сигнал запроса на открытие окна авторизации.
     */
    void showAuthRequested();
};