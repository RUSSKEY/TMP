/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBoxEquation;
    QFormLayout *formLayout;
    QLabel *labelA;
    QDoubleSpinBox *doubleSpinBoxA;
    QLabel *labelB;
    QDoubleSpinBox *doubleSpinBoxB;
    QLabel *labelEpsilon;
    QDoubleSpinBox *doubleSpinBoxEpsilon;
    QPushButton *pushButtonSolveEquation;
    QLineEdit *funcInput;
    QLabel *label;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEditInput;
    QPushButton *pushButtonLoadImage;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonProcess;
    QPushButton *pushButtonDecode;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QTextEdit *textEdit;
    QPushButton *pushButtonLogout;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(600, 708);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: #2E3440;\n"
"color: #D8DEE9;"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        groupBoxEquation = new QGroupBox(centralwidget);
        groupBoxEquation->setObjectName("groupBoxEquation");
        formLayout = new QFormLayout(groupBoxEquation);
        formLayout->setObjectName("formLayout");
        labelA = new QLabel(groupBoxEquation);
        labelA->setObjectName("labelA");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, labelA);

        doubleSpinBoxA = new QDoubleSpinBox(groupBoxEquation);
        doubleSpinBoxA->setObjectName("doubleSpinBoxA");
        doubleSpinBoxA->setValue(1.000000000000000);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, doubleSpinBoxA);

        labelB = new QLabel(groupBoxEquation);
        labelB->setObjectName("labelB");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, labelB);

        doubleSpinBoxB = new QDoubleSpinBox(groupBoxEquation);
        doubleSpinBoxB->setObjectName("doubleSpinBoxB");
        doubleSpinBoxB->setValue(2.000000000000000);

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, doubleSpinBoxB);

        labelEpsilon = new QLabel(groupBoxEquation);
        labelEpsilon->setObjectName("labelEpsilon");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, labelEpsilon);

        doubleSpinBoxEpsilon = new QDoubleSpinBox(groupBoxEquation);
        doubleSpinBoxEpsilon->setObjectName("doubleSpinBoxEpsilon");
        doubleSpinBoxEpsilon->setDecimals(6);
        doubleSpinBoxEpsilon->setSingleStep(0.000100000000000);
        doubleSpinBoxEpsilon->setValue(0.001000000000000);

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, doubleSpinBoxEpsilon);

        pushButtonSolveEquation = new QPushButton(groupBoxEquation);
        pushButtonSolveEquation->setObjectName("pushButtonSolveEquation");
        pushButtonSolveEquation->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #D08770;\n"
"    color: #2E3440;\n"
"    border-radius: 4px;\n"
"    padding: 8px;\n"
"    min-width: 100px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #EBCB8B;\n"
"}"));

        formLayout->setWidget(4, QFormLayout::ItemRole::SpanningRole, pushButtonSolveEquation);

        funcInput = new QLineEdit(groupBoxEquation);
        funcInput->setObjectName("funcInput");
        funcInput->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: #3B4252;\n"
"    color: #E5E9F0;\n"
"    border: 1px solid #4C566A;\n"
"    border-radius: 4px;\n"
"    padding: 8px;\n"
"}"));

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, funcInput);

        label = new QLabel(groupBoxEquation);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);


        verticalLayout->addWidget(groupBoxEquation);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        lineEditInput = new QLineEdit(groupBox);
        lineEditInput->setObjectName("lineEditInput");
        lineEditInput->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: #3B4252;\n"
"    color: #E5E9F0;\n"
"    border: 1px solid #4C566A;\n"
"    border-radius: 4px;\n"
"    padding: 8px;\n"
"}"));

        verticalLayout_2->addWidget(lineEditInput);

        pushButtonLoadImage = new QPushButton(groupBox);
        pushButtonLoadImage->setObjectName("pushButtonLoadImage");
        pushButtonLoadImage->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #A3BE8C;\n"
"    color: #2E3440;\n"
"    border-radius: 4px;\n"
"    padding: 8px;\n"
"    min-width: 100px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #B5D99C;\n"
"}"));

        verticalLayout_2->addWidget(pushButtonLoadImage);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButtonProcess = new QPushButton(groupBox);
        pushButtonProcess->setObjectName("pushButtonProcess");
        pushButtonProcess->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #5E81AC;\n"
"    color: white;\n"
"    border-radius: 4px;\n"
"    padding: 8px;\n"
"    min-width: 100px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #81A1C1;\n"
"}"));

        horizontalLayout->addWidget(pushButtonProcess);

        pushButtonDecode = new QPushButton(groupBox);
        pushButtonDecode->setObjectName("pushButtonDecode");
        pushButtonDecode->setMinimumSize(QSize(116, 0));
        pushButtonDecode->setMouseTracking(true);
        pushButtonDecode->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #5E81AC;\n"
"    color: white;\n"
"    border-radius: 4px;\n"
"    padding: 8px;\n"
"    min-width: 100px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #81A1C1;\n"
"}"));

        horizontalLayout->addWidget(pushButtonDecode);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        textEdit = new QTextEdit(groupBox_2);
        textEdit->setObjectName("textEdit");
        textEdit->setStyleSheet(QString::fromUtf8("QTextEdit {\n"
"    background-color: #3B4252;\n"
"    color: #E5E9F0;\n"
"    border: 1px solid #4C566A;\n"
"    border-radius: 4px;\n"
"    padding: 8px;\n"
"}"));
        textEdit->setReadOnly(true);

        verticalLayout_3->addWidget(textEdit);


        verticalLayout->addWidget(groupBox_2);

        pushButtonLogout = new QPushButton(centralwidget);
        pushButtonLogout->setObjectName("pushButtonLogout");
        pushButtonLogout->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #BF616A;\n"
"    color: white;\n"
"    border-radius: 4px;\n"
"    padding: 8px;\n"
"    min-width: 100px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #D08770;\n"
"}"));

        verticalLayout->addWidget(pushButtonLogout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 600, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Crypto Application", nullptr));
        groupBoxEquation->setTitle(QCoreApplication::translate("MainWindow", "\320\240\320\265\321\210\320\265\320\275\320\270\320\265 \321\203\321\200\320\260\320\262\320\275\320\265\320\275\320\270\320\271 (\320\234\320\265\321\202\320\276\320\264 \321\205\320\276\321\200\320\264)", nullptr));
        labelA->setText(QCoreApplication::translate("MainWindow", "a:", nullptr));
        labelB->setText(QCoreApplication::translate("MainWindow", "b:", nullptr));
        labelEpsilon->setText(QCoreApplication::translate("MainWindow", "Epsilon:", nullptr));
        pushButtonSolveEquation->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\321\210\320\270\321\202\321\214 \321\203\321\200\320\260\320\262\320\275\320\265\320\275\320\270\320\265", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "f(x):", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\276\320\264", nullptr));
        lineEditInput->setText(QString());
        lineEditInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\202\320\265\320\272\321\201\321\202 \320\262\320\275\320\265\320\264\321\200\321\217\320\265\320\274\320\276\320\263\320\276 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\321\217", nullptr));
        pushButtonLoadImage->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265", nullptr));
        pushButtonProcess->setText(QCoreApplication::translate("MainWindow", "\320\222\320\275\320\265\320\264\321\200\320\270\321\202\321\214 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\265", nullptr));
        pushButtonDecode->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\321\201\321\202\320\260\321\202\321\214 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\265", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\262\320\276\320\264", nullptr));
        pushButtonLogout->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\271\321\202\320\270 \320\270\320\267 \320\260\320\272\320\272\320\260\321\203\320\275\321\202\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
