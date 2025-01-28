#include "DtRxTxParser.h"

static uint8_t sFifoRxBuff[1024] = { 0 };
static uint8_t sFifoTxBuff[1024] = { 0 };

static uint8_t sProtRxBuff[1024] = { 0 };
static uint8_t sProtTxBuff[1024] = { 0 };

RxTxParser::RxTxParser()
    : mRxFifo(sFifoRxBuff, sizeof(sFifoRxBuff)),
    mTxFifo(sFifoTxBuff, sizeof(sFifoTxBuff)),
    mProtocol(Dt::DtRoleType::kMaster, sProtRxBuff, sizeof(sProtRxBuff), sProtTxBuff, sizeof(sProtTxBuff))
{
    mRxFifo = Dt::DtFifo(sFifoRxBuff, sizeof(sFifoRxBuff));
    mTxFifo = Dt::DtFifo(sFifoTxBuff, sizeof(sFifoTxBuff));

    //connect(&udpServer, &UdpServer::errorMessage, this, &RxTxParser::errMessage);
    //connect(&udpServer, &UdpServer::errorMessage, &RxTxParser::errMessage);
    //connect(&udpServer, &UdpServer::warningMessage, &RxTxParser::warnMessage);
    //connect(&udpServer, &UdpServer::infoMessage, &RxTxParser::infMessage);
    //connect(&udpServer, &UdpServer::dataReceived, &RxTxParser::dataReceived);
}

void RxTxParser::start(const UdpServer::Config_t &config)
{

}

void RxTxParser::errMessage(const QString &message)
{
    emit errorMessage(message);
}



void RxTxParser::dataReceived(const QByteArray &data)
{

}
