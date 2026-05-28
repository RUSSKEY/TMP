#include "authregcontainer.h"
#include <QtWidgets/QBoxLayout>

AuthRegContainer::AuthRegContainer(QWidget *parent) : QWidget(parent) {
    stackedWidget = new QStackedWidget(this);

    authDialog = new AuthDialog();
    regDialog = new RegisterDialog();

    stackedWidget->addWidget(authDialog);
    stackedWidget->addWidget(regDialog);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(stackedWidget);
    setLayout(layout);

    // РџРѕРґРєР»СЋС‡РµРЅРёРµ СЃРёРіРЅР°Р»РѕРІ РґР»СЏ РїРµСЂРµРєР»СЋС‡РµРЅРёСЏ РѕРєРѕРЅ
    connect(authDialog, &AuthDialog::showRegisterRequested, this, [this]() {
        stackedWidget->setCurrentWidget(regDialog);
    });

    connect(regDialog, &RegisterDialog::showAuthRequested, this, [this]() {
        stackedWidget->setCurrentWidget(authDialog);
    });
}
