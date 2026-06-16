#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "singletonclient.h"
#include <QFileDialog>
#include <cmath>
#include <QMessageBox>
#include <QStackedWidget>

MainWindow::MainWindow(QString role, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_userRole(role) // Сохраняем переданную роль в приватную переменную
{
    //
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);

    // Настройка блока уравнений
    ui->groupBoxEquation->setTitle("Решение кубических уравнений Ax³+Bx²+Cx+D=0 (Метод хорд)");
    ui->funcInput->setPlaceholderText("Задайте коэффициенты через двоеточие -> A:B:C:D (например, 1:0:-3:1)");

    // 2. ДИФФЕРЕНЦИАЦИЯ ИНТЕРФЕЙСА
    if (m_userRole == "admin") {
        setWindowTitle("ПАНЕЛЬ АДМИНИСТРАТОРА");
        ui->groupBox_2->setTitle("Управление Базой Данных / Вывод");
        ui->pushButtonProcess->setText("Выполнить админ-команду");
        ui->lineEditInput->setPlaceholderText("Введите: get_users_sorted ИЛИ search_user:логин ИЛИ delete:логин");
    } else {
        setWindowTitle("Пользовательский режим");
        ui->groupBox_2->setTitle("Обработка данных / Вывод");
        ui->pushButtonProcess->setText("Обработать");
        ui->lineEditInput->setPlaceholderText("Введите текст для отправки на сервер...");
    }

    // Вывод последнего ответа, если он был
    QString lastResponse = SingletonClient::instance()->latestResponse();
    if (!lastResponse.isEmpty()) {
        ui->textEdit->append("> Last response:\n" + lastResponse);
    }

    connect(ui->pushButtonProcess, &QPushButton::clicked, this, &MainWindow::on_pushButtonProcess_clicked);
    connect(ui->pushButtonLoadImage, &QPushButton::clicked, this, &MainWindow::on_pushButtonLoadImage_clicked);
    connect(ui->pushButtonSolveEquation, &QPushButton::clicked, this, &MainWindow::on_pushButtonSolveEquation_clicked);
    connect(ui->pushButtonLogout, &QPushButton::clicked, this, &MainWindow::on_pushButtonLogout_clicked);

    connect(SingletonClient::instance(), &SingletonClient::responseReceived, this, [this](const QString& text) {
        if (text.contains("Error:")) {
            ui->textEdit->append("> Error: " + text);
        } else {
            ui->textEdit->append("> Server response:\n" + text);
        }
    });
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButtonProcess_clicked()
{
    QString input = ui->lineEditInput->text().trimmed();
    if (input.isEmpty()) return;

    if (m_userRole == "admin") {
        // Если это админ, мы шлем команду как есть прямо в сокет
        // Чтобы сервер понял админа, обернем команду в префикс "equation: "
        QString adminCmd = "equation: " + input;

        ui->textEdit->append("> Отправка админ-команды: " + input);
        SingletonClient::instance()->transmitCommand(adminCmd);
    } else {
        // Обычный пользователь
        QString command = "ENCRYPT:" + input;
        ui->textEdit->append("> Sending text to encrypt: " + input);
        SingletonClient::instance()->transmitCommand(command);
    }
}

void MainWindow::on_pushButtonLoadImage_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.bmp)");
    if (!filePath.isEmpty()) {
        currentImagePath = filePath;
        ui->textEdit->append("> Image loaded: " + filePath);
    }
}

void MainWindow::on_pushButtonSolveEquation_clicked()
{
    QString func = ui->funcInput->text().trimmed();
    double a = ui->doubleSpinBoxA->value();
    double b = ui->doubleSpinBoxB->value();
    double epsilon = ui->doubleSpinBoxEpsilon->value();

    if (a >= b) {
        QMessageBox::warning(this, "Error", "Value 'a' must be less than 'b'");
        return;
    }

    QString equationCmd = QString("equation: %1:%2:%3:%4")
                              .arg(func)
                              .arg(a)
                              .arg(b)
                              .arg(epsilon);

    ui->textEdit->append("> Sending equation to server: " + equationCmd);
    SingletonClient::instance()->transmitCommand(equationCmd);
}

void MainWindow::on_pushButtonLogout_clicked()
{
    if (this->parentWidget()) {
        QStackedWidget *stacked = this->parentWidget()->findChild<QStackedWidget*>();
        QWidget *authWin = this->parentWidget()->findChild<QWidget*>("AuthDialog");

        if (stacked && authWin) {
            stacked->setCurrentWidget(authWin);
        } else if (stacked) {
            // Если findChild не нашёл по имени, просто переключаем на первый виджет (окно логина)
            stacked->setCurrentIndex(0);
        }

        this->parentWidget()->show();
    }
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->close();
}