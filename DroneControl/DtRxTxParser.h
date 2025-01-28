#ifndef DTRXTXPARSER_H
#define DTRXTXPARSER_H

#include <QObject>
#include <QThread>
#include <QString>

#include "DtCommand.h"
#include "DtProtocol.h"
#include "DtUdpServer.h"

class RxTxParser : QObject
{
Q_OBJECT
public:
    explicit RxTxParser();
    void start(const UdpServer::Config_t &config);

signals:
    void errorMessage(const QString &message);
    void warningMessage(const QString &message);
    void infoMessage(const QString &message);

private slots:
    void errMessage(const QString &message);
    // void warnMessage(const QString &message);
    // void infMessage(const QString &message);
    void dataReceived(const QByteArray &data);

private:
    Dt::DtFifo mRxFifo;
    Dt::DtFifo mTxFifo;
    Dt::DtProtocol mProtocol;
    UdpServer udpServer;
    QThread m_thread;
};

#endif // DTRXTXPARSER_H
