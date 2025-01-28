#include "DtUdpServer.h"

UdpServer::UdpServer()
{
    connect(&serverSocket, &QAbstractSocket::readyRead, this, &UdpServer::readyRead);
}

UdpServer::~UdpServer()
{
    shutdown();
}

bool UdpServer::run (const Config_t &config)
{
    mConfig.listenAddress = config.listenAddress;
    mConfig.listenPort = config.listenPort;
    mConfig.sendAddress = config.sendAddress;
    mConfig.sendPort = config.sendPort;
    if (mConfig.listenAddress != serverSocket.localAddress() || mConfig.listenPort != serverSocket.localPort()) {
        shutdown();
        listening = serverSocket.bind(mConfig.listenAddress, mConfig.listenPort);
        if (!listening)
            emit errorMessage(serverSocket.errorString());
    } else {
        listening = true;
    }

    return listening;
}

bool UdpServer::isListening() const
{
    return listening;
}

void UdpServer::close()
{
    serverSocket.close();
    listening = false;
}

void UdpServer::shutdown()
{
    serverSocket.close();
}

void UdpServer::readyRead()
{

    const qint64 bytesToRead = serverSocket.pendingDatagramSize();
    if (bytesToRead <= 0) {
        emit warningMessage(tr("A spurious read notification"));
        return;
    }

    QByteArray dgram(bytesToRead, Qt::Uninitialized);
    QHostAddress peerAddress;
    quint16 peerPort = 0;
    const qint64 bytesRead = serverSocket.readDatagram(dgram.data(), dgram.size(),
                                                       &peerAddress, &peerPort);
    if (bytesRead <= 0) {
        emit warningMessage(tr("Failed to read a datagram: ") + serverSocket.errorString());
        return;
    }

    dgram.resize(bytesRead);

    if (peerAddress.isNull() || !peerPort) {
        emit warningMessage(tr("Failed to extract peer info (address, port)"));
        return;
    }


    if (dgram.size() != 0) {
        emit dataReceived(dgram);
    }
}

bool UdpServer::write(const QByteArray &data)
{
    bool result = false;

    if (!mConfig.sendAddress.isNull()) {
        result = serverSocket.writeDatagram(data, mConfig.sendAddress, mConfig.sendPort);
    }
    return result;
}
