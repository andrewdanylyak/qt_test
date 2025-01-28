#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "appsetupdialog.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&parser, &Parser::errorMessage, this, &MainWindow::addErrorMessage);
    connect(&parser, &Parser::warningMessage, this, &MainWindow::addWarningMessage);
    connect(&parser, &Parser::infoMessage, this, &MainWindow::addInfoMessage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_mSettingsButton_clicked()
{
    AppSetupDialog appSetupDialog;
    UdpServer::Config_t config {};
    if (appSetupDialog.exec() == QDialog::Accepted) {
        config.listenAddress = appSetupDialog.orinRxIp();
        config.listenPort = appSetupDialog.orinRxPort();
        config.sendAddress = appSetupDialog.orinTxIp();
        config.sendPort = appSetupDialog.orinTxPort();
        videoPath = appSetupDialog.videoPath();
        parser.start(config);
    }

}

void MainWindow::on_pushButton_clicked()
{
    parser.cmdGetStatus();
}

void MainWindow::addErrorMessage(const QString &message)
{

    qDebug("%s", qPrintable(message));
}

void MainWindow::addWarningMessage(const QString &message)
{
    qDebug("%s", qPrintable(message));
}

void MainWindow::addInfoMessage(const QString &message)
{
    qDebug("%s", qPrintable(message));
}

