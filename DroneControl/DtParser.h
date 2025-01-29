#ifndef DTPARSER_H
#define DTPARSER_H

#include <QObject>
#include <QThread>
#include <QDateTime>
#include <QDebug>

#include "DtCommand.h"
#include "DtProtocol.h"
#include "DtUdpServer.h"

class Parser : public QObject
{
    Q_OBJECT
public:

    Parser();
    ~Parser();

    void config(const UdpServer::Config_t &config);
    void cmdGetStatus();
signals:
    void errorMessage(const QString &message);
    void warningMessage(const QString &message);
    void infoMessage(const QString &message);
    void finished();

public slots:
    void process();
    void stop();

private slots:
    void errMessage(const QString &message);
    void warnMessage(const QString &message);
    void infMessage(const QString &message);
    void dataReceived(const QByteArray &data);

private:
    static Parser *getInstance() {
        Parser sThis;
        return &sThis;
    }
    UdpServer udpServer;
    Dt::DtFifo mRxFifo;
    Dt::DtFifo mTxFifo;
    Dt::DtProtocol mProtocol;
    QThread mThread;
    //void sendProtocol();
    static void sGetStatus(const uint8_t* pData , size_t size);
    std::atomic<bool> mRunning = false;
};

#endif // DTPARSER_H
