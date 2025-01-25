#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setupdialog.h"

#include <QDebug>

const QString colorizer(QStringLiteral("<font color=\"%1\">%2</font><br>"));

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&orinPodServer, &UdpServer::errorMessage, this, &MainWindow::addErrorMessage);
    connect(&orinPodServer, &UdpServer::warningMessage, this, &MainWindow::addWarningMessage);
    connect(&orinPodServer, &UdpServer::infoMessage, this, &MainWindow::addInfoMessage);
    connect(&orinPodServer, &UdpServer::datagramReceived, this, &MainWindow::addClientMessage);

    // connect(&orinServer2, &UdpServer::errorMessage, this, &MainWindow::addErrorMessage);
    // connect(&orinServer2, &UdpServer::warningMessage, this, &MainWindow::addWarningMessage);
    // connect(&orinServer2, &UdpServer::infoMessage, this, &MainWindow::addInfoMessage);
    // connect(&orinServer2, &UdpServer::datagramReceived, this, &MainWindow::addClientMessage);

    updateUi();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_mOpenButton_clicked()
{
    if (!orinPodServer.isListening()) {
        SetupDialog sSetupDialog;

        if (sSetupDialog.exec() == QDialog::Accepted) {
            address = sSetupDialog.selectedIp();
            orinPodPort = sSetupDialog.selectedOrinPort();
            if (address.isNull()) {
                addErrorMessage(tr("Failed to start listening, no valid address/port"));
            } else if (orinPodServer.listen(address, orinPodPort)) {
                addInfoMessage(tr("Server is listening on address %1 and port %2")
                                   .arg(address.toString())
                                   .arg(orinPodPort));
            }
        }
        else {
            orinPodServer.close();
            addInfoMessage(tr("Server is not accepting new connections"));
        }
    }

    updateUi();
}

void MainWindow::on_mCloseButton_clicked()
{
    QCoreApplication::exit(0);
}

void MainWindow::on_mWriteButton_clicked()
{
    QByteArray data;
    data.fill('a', 10);
    // QString str = ui->lineEdit->text();
    // for(int i = 0; i < str.size(); i++)
    //     QString ch = str[i];
    //     data.append(ch.to);
    orinPodServer.write(data);
}

void MainWindow::updateUi()
{
    orinPodServer.isListening() ? ui->mOpenButton->setText(tr("Stop listening"))
                         : ui->mOpenButton->setText(tr("Start listening"));
}

void MainWindow::addErrorMessage(const QString &message)
{
    ui->mMsgBox->insertHtml(colorizer.arg(QStringLiteral("Crimson"), message));
}

void MainWindow::addWarningMessage(const QString &message)
{
    ui->mMsgBox->insertHtml(colorizer.arg(QStringLiteral("DarkOrange"), message));
}

void MainWindow::addInfoMessage(const QString &message)
{
    ui->mMsgBox->insertHtml(colorizer.arg(QStringLiteral("DarkBlue"), message));
}

void MainWindow::addClientMessage(const QString &peerInfo,
                                  const QByteArray &plainText)
{
    static const QString messageColor = QStringLiteral("DarkMagenta");
    static const QString formatter = QStringLiteral("<br>A message from %1 : %2");

    // const QString html = formatter.arg(peerInfo,
    //                                    QString::fromUtf8(plainText.toHex(' ')));
    // ui->mMsgBox->insertHtml(colorizer.arg(messageColor, html));
    const QString html1 = formatter.arg(peerInfo,
                         QString::fromUtf8(plainText));
    ui->mMsgBox->insertHtml(colorizer.arg(messageColor, html1));
}


