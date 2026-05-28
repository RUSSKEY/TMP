#pragma once

#include <QtWidgets/QWidget>
#include <QStackedWidget>
#include "authdialog.h"
#include "regdialog.h"

/**
 * @brief Контейнер для переключения между окнами авторизации и регистрации.
 *
 * Использует QStackedWidget для плавного переключения между двумя диалогами.
 * Обеспечивает единую точку входа в приложение.
 *
 * @author CryptoApp Team
 * @version 1.0
 */
class AuthRegContainer : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Конструктор контейнера.
     *
     * Создает и настраивает стековый виджет с двумя диалогами,
     * подключает сигналы для переключения между ними.
     *
     * @param parent Родительский виджет (по умолчанию nullptr)
     */
    explicit AuthRegContainer(QWidget* parent = nullptr);

private:
    QStackedWidget* stackedWidget;    ///< Стековый виджет для переключения окон
    AuthDialog* authDialog;           ///< Диалог авторизации
    RegisterDialog* regDialog;        ///< Диалог регистрации
};