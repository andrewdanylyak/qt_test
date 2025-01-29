#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "appsetupdialog.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupSlots();

}

MainWindow::~MainWindow()
{
    stopThreads();
    delete ui;
}

void MainWindow::setupSlots()
{
    connect(&parser, &Parser::errorMessage, this, &MainWindow::addErrorMessage);
    connect(&parser, &Parser::warningMessage, this, &MainWindow::addWarningMessage);
    connect(&parser, &Parser::infoMessage, this, &MainWindow::addInfoMessage);
    connect(ui->mSettingsButton,&QPushButton::clicked, this, &MainWindow::onSettingsClicked);
    connect(ui->actionSettings, &QAction::triggered, this, &MainWindow::onSettingsClicked);
    connect(ui->pushButton,&QPushButton::clicked, this, &MainWindow::onPushButtonClicked);
}

void MainWindow::onSettingsClicked()
{
    AppSetupDialog appSetupDialog;
    UdpServer::Config_t config {};
    if (appSetupDialog.exec() == QDialog::Accepted) {
        config.listenAddress = appSetupDialog.orinRxIp();
        config.listenPort = appSetupDialog.orinRxPort();
        config.sendAddress = appSetupDialog.orinTxIp();
        config.sendPort = appSetupDialog.orinTxPort();
        videoPath = appSetupDialog.videoPath();
        parser.config(config);

        parser.moveToThread(&mThread);
        connect(&mThread, &QThread::started, &parser, &Parser::process);
        connect(&parser, &Parser::finished, &mThread, &QThread::quit);
        connect(this, &MainWindow::stopAll, &parser, &Parser::stop);
        connect(&parser, &Parser::finished, &parser, &Parser::deleteLater);
        connect(&mThread, &QThread::finished, &mThread, &QThread::deleteLater);
        mThread.start();

        QString url1 = "rtsp://192.168.144.21:8554/test";
        ui->gridLayout->addWidget(&mVideoWidget);
        mVideoWidget.resize(800, 600);
        mVideoWidget.playStream(videoPath);
    }

}

void MainWindow::stopThreads()
{
    emit stopAll();
}


void MainWindow::onPushButtonClicked()
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

