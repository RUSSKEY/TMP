#include "authdialog.h"
#include "ui_authdialog.h"
#include "regdialog.h"
#include "singletonclient.h"
#include "mainwindow.h"

AuthDialog::AuthDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::AuthDialog)
{
    ui->setupUi(this);
    SingletonClient::instance()->establishConnection();
    setWindowTitle("Login");
    ui->textEditStatus->setReadOnly(true);

    connect(SingletonClient::instance(), &SingletonClient::responseReceived, this, [this](const QString& text) {
        if (this->parentWidget() && !this->parentWidget()->isVisible()) {
            return;
        }

        ui->textEditStatus->append("> Response:\n" + text);

        if (text.contains("Authentication successful", Qt::CaseInsensitive)) {
            QWidget *container = this->parentWidget();
            if (container) {
                // Вырезаем роль после двоеточия (если двоеточия нет, по дефолту 'user')
                QString role = "user";
                if (text.contains(":")) {
                    role = text.split(":").last().trimmed();
                }

                // Передаем роль в конструктор MainWindow
                MainWindow *mainWin = new MainWindow(role, container);
                mainWin->setAttribute(Qt::WA_DeleteOnClose);
                mainWin->show();

                container->hide();
            }

            ui->textEditStatus->clear();
            ui->lineEditPassword->clear();
        }
    });

    connect(ui->pushButtonRegister, &QPushButton::clicked, this, &AuthDialog::on_pushButtonRegister_clicked);
    connect(ui->pushButtonLogin, &QPushButton::clicked, this, &AuthDialog::on_pushButtonLogin_clicked);

    QString lastResponse = SingletonClient::instance()->latestResponse();
    if (!lastResponse.isEmpty()) {
        ui->textEditStatus->append("> Last response:\n" + lastResponse);
    }
}

AuthDialog::~AuthDialog() {
    delete ui;
}

void AuthDialog::on_pushButtonLogin_clicked()
{
    QString username = ui->lineEditUsername->text().trimmed();
    QString password = ui->lineEditPassword->text().trimmed();

    if (username.isEmpty() || password.isEmpty()) {
        ui->textEditStatus->append("Error: Fields cannot be empty");
        return;
    }

    QString command = QString("auth %1:%2").arg(username, password);
    SingletonClient::instance()->transmitCommand(command);
}