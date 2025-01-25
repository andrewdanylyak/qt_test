#include "udpserver.h"

UdpServer::UdpServer()
{
    connect(&serverSocket, &QAbstractSocket::readyRead, this, &UdpServer::readyRead);
}

UdpServer::~UdpServer()
{
    shutdown();
}

bool UdpServer::listen(const QHostAddress &address, quint16 port)
{
    if (address != serverSocket.localAddress() || port != serverSocket.localPort()) {
        shutdown();
        listening = serverSocket.bind(address, port);
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

void UdpServer::readyRead()
{
    //! [3]
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
    //! [3]
    //! [4]
    if (peerAddress.isNull() || !peerPort) {
        emit warningMessage(tr("Failed to extract peer info (address, port)"));
        return;
    }

    const QString peerInfo = peer_info(peerAddress, peerPort);

    if (dgram.size() != 0) {
        emit datagramReceived(peerInfo, dgram);
    }

    // mHostAddress = peerAddress;
    // mPort = peerPort;

    // const auto client = std::find_if(knownClients.begin(), knownClients.end(),
    //                                  [&](const std::unique_ptr<QDtls> &connection){
    //                                      return connection->peerAddress() == peerAddress
    //                                             && connection->peerPort() == peerPort;
    //                                  });
    // //! [4]

    // //! [5]
    // if (client == knownClients.end())
    //     return handleNewConnection(peerAddress, peerPort, dgram);
    // //! [5]

    // //! [6]
    // if ((*client)->isConnectionEncrypted()) {
    //     decryptDatagram(client->get(), dgram);
    //     if ((*client)->dtlsError() == QDtlsError::RemoteClosedConnectionError)
    //         knownClients.erase(client);
    //     return;
    // }
    // //! [6]

    // //! [7]
    // doHandshake(client->get(), dgram);
    //! [7]
}

void UdpServer::shutdown()
{
    // for (const auto &connection : std::exchange(knownClients, {}))
    //     connection->shutdown(&serverSocket);
    serverSocket.close();
}

QString UdpServer::peer_info(const QHostAddress &address, quint16 port)
{
    const static QString info = QStringLiteral("(%1:%2)");
    return info.arg(address.toString()).arg(port);
}

bool UdpServer::write(const QByteArray &data)
{
    bool result = false;
    mHostAddress = QHostAddress("192.168.144.21");
    if (!mHostAddress.isNull()) {
        result = serverSocket.writeDatagram(data, mHostAddress, 5000);
    }
    return result;
}
