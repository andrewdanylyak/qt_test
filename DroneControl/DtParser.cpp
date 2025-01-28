#include "DtParser.h"

static uint8_t sFifoRxBuff[1024] = { 0 };
static uint8_t sFifoTxBuff[1024] = { 0 };

static uint8_t sProtRxBuff[1024] = { 0 };
static uint8_t sProtTxBuff[1024] = { 0 };

Parser::Parser()
    : mRxFifo(sFifoRxBuff, sizeof(sFifoRxBuff)),
    mTxFifo(sFifoTxBuff, sizeof(sFifoTxBuff)),
    mProtocol(Dt::DtRoleType::kMaster, sProtRxBuff, sizeof(sProtRxBuff), sProtTxBuff, sizeof(sProtTxBuff))
{

    mRxFifo = Dt::DtFifo(sFifoRxBuff, sizeof(sFifoRxBuff));
    mTxFifo = Dt::DtFifo(sFifoTxBuff, sizeof(sFifoTxBuff));

    connect(&udpServer, &UdpServer::errorMessage, this, &Parser::errMessage);
    connect(&udpServer, &UdpServer::warningMessage, this, &Parser::warnMessage);
    connect(&udpServer, &UdpServer::infoMessage, this, &Parser::infMessage);
    connect(&udpServer, &UdpServer::dataReceived, this, &Parser::dataReceived);
    //connect(&mThread, &QThread::finished, this, &QObject::deleteLater);

    mProtocol.setFuncForGetTimeStamp([]() {
        return (uint32_t)QDateTime::currentMSecsSinceEpoch();
    });

    mProtocol.setTimeoutCallback([](){
        qErrnoWarning("Timeout\n");
    });

    Dt::DtProtocolCommand_t getStatus = {
        static_cast<uint8_t>(Dt::DtCommandEnum::kCmdGetStatus),
        [=](const uint8_t* pData , size_t size){

            uint8_t buffer[CMD_ID_SIZE + 1] = { 0 };
            buffer[0] = static_cast<uint8_t>(Dt::DtCommandEnum::kCmdStatus);
            buffer[1] = 0x34;
            mProtocol.prepareToSend(buffer, sizeof(buffer));
        }
    };

    mProtocol.addCommand(getStatus);

    mProtocol.setAckCallback([](Dt::DtProtocolAckEnum ack){
        using Ack = Dt::DtProtocolAckEnum;
        switch (ack)
        {
        case Ack::kProtocolAck_OK:
            qDebug("kProtocolAck_OK\n");
            break;
        case Ack::kProtocolAck_SyncError:
            qDebug("kProtocolAck_SyncError\n");
            break;
        case Ack::kProtocolAck_BadCRC:
            qDebug("kProtocolAck_BadCRC\n");
            break;
        case Ack::kProtocolAck_MissingFrame:
            qDebug("kProtocolAck_MissingFrame\n");
            break;
        case Ack::kProtocolAck_OutOfMemory:
            qDebug("kProtocolAck_OutOfMemory\n");
            break;
        case Ack::kProtocolAck_None:
            qDebug("kProtocolAck_None\n");
            break;
        default:
            qDebug("default\n");
            break;
        }
    });
}

Parser::~Parser()
{
    //mThread.terminate();
    running = false;
    //mThread.wait();
}

void Parser::start(const UdpServer::Config_t &config)
{
    if (!config.listenAddress.isNull() || !config.sendAddress.isNull()) {
        udpServer.run(config);
        infMessage(tr("Server is listening on address %1 and port %2")
                           .arg(config.listenAddress.toString())
                           .arg(config.listenPort));
        connect(&mThread, &QThread::started, [=](){sendProtocol();});
        running = true;
        mThread.start();
    } else {
        errMessage(tr("Failed to start listening, no valid address/port"));
    }
}

void Parser::errMessage(const QString &message)
{
    emit errorMessage(message);
}

void Parser::warnMessage(const QString &message)
{
    emit warningMessage(message);
}

void Parser::infMessage(const QString &message)
{
    emit infoMessage(message);
}

void Parser::dataReceived(const QByteArray &data)
{
    uint8_t buffer[data.size()];
    size_t size = data.size();
    std::memcpy(buffer, data.data(), size);
    mRxFifo.pushBuffer(buffer, size);
    qDebug("Data received");
}

void Parser::sendProtocol() {
    uint8_t buffer[128] = { 0 };
    while (running) {
        uint16_t size = 0;
        size = mTxFifo.getSize();
        if (size > 0) {
            mTxFifo.popBuffer(buffer, size);
            QByteArray array;
            array.resize(size);
            memcpy(array.data(), buffer, size);
            udpServer.write(array);
        }
        mProtocol.parser(&mRxFifo);
        mProtocol.send(&mTxFifo, 100);
    }
}

void Parser::cmdGetStatus()
{
    uint8_t cmd = static_cast<uint8_t>(Dt::DtCommandEnum::kCmdGetStatus);
    mProtocol.prepareToSend(&cmd, sizeof(cmd));
}

void Parser::sGetStatus(const uint8_t* pData , size_t size)
{
    //uint8_t buffer[CMD_ID_SIZE + 128] = { 0 };
    //buffer[0] = static_cast<uint8_t>(Dt::DtCommandEnum::kCmdStatus);
    //buffer[1] = 0x34;
   // memset(&buffer[1], 0x55, sizeof(buffer) - 1);
    //getInstance()->mProtocol.prepareToSend(buffer, sizeof(buffer));
    qDebug("Get status len: %lu\n", size);
}
