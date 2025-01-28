#include "appsetupdialog.h"
#include "ui_appsetupdialog.h"

AppSetupDialog::AppSetupDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AppSetupDialog)
{
    ui->setupUi(this);
    auto rxPortValidator = new QIntValidator(0, int(std::numeric_limits<quint16>::max()),
                                            ui->mOrinReceivePortLineEdit);
    ui->mOrinReceivePortLineEdit->setValidator(rxPortValidator);
    ui->mOrinTransmitPortLineEdit->setText("5000");
    auto txPortValidator = new QIntValidator(0, int(std::numeric_limits<quint16>::max()),
                                             ui->mOrinTransmitPortLineEdit);
    ui->mOrinTransmitPortLineEdit->setValidator(txPortValidator);
    ui->mOrinTransmitPortLineEdit->setText("5000");
}

AppSetupDialog::~AppSetupDialog()
{
    delete ui;
}

QHostAddress AppSetupDialog::orinRxIp() const
{
    return QHostAddress(ui->mOrinReceiveIpLineEdit->text());
}

quint16 AppSetupDialog::orinRxPort() const
{
    return quint16(ui->mOrinReceivePortLineEdit->text().toUInt());
}

QHostAddress AppSetupDialog::orinTxIp() const
{
    return QHostAddress(ui->mOrinTransmitIpLineEdit->text());
}

quint16 AppSetupDialog::orinTxPort() const
{
    return quint16(ui->mOrinTransmitPortLineEdit->text().toUInt());
}

QString AppSetupDialog::videoPath() const
{
    return ui->mVidePathLineEdit->text();
}
