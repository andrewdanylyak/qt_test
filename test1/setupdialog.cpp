#include <limits>

#include <QtCore>
#include <QtNetwork>

#include "setupdialog.h"
#include "ui_setupdialog.h"

SetupDialog::SetupDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SetupDialog)
{
    ui->setupUi(this);
    auto port1Validator = new QIntValidator(0, int(std::numeric_limits<quint16>::max()),
                                           ui->mPodContorlPortLineEdit);
    ui->mPodContorlPortLineEdit->setValidator(port1Validator);
    ui->mPodContorlPortLineEdit->setText(QStringLiteral("5000"));

    auto port2Validator = new QIntValidator(0, int(std::numeric_limits<quint16>::max()),
                                            ui->mPodContorlVideoPortLineEdit);
    ui->mPodContorlVideoPortLineEdit->setValidator(port2Validator);
    ui->mPodContorlVideoPortLineEdit->setText(QStringLiteral("5001"));

    const QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    availableAddresses.reserve(ipAddressesList.size());
    for (const QHostAddress &ip : ipAddressesList) {
        if (ip != QHostAddress::LocalHost && ip.toIPv4Address()) {
            availableAddresses.push_back(ip);
            ui->mIpAddrComboBox->addItem(ip.toString());
        }
    }
}

SetupDialog::~SetupDialog()
{
    delete ui;
}

QHostAddress SetupDialog::selectedIp() const
{
    if (!availableAddresses.size())
        return {};

    return availableAddresses[ui->mIpAddrComboBox->currentIndex()];
}

quint16 SetupDialog::selectedOrinPort() const
{
    return quint16(ui->mPodContorlPortLineEdit->text().toUInt());
}
