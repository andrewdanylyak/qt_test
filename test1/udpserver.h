#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QtNetwork>

class UdpServer : public QObject
{
    Q_OBJECT
public:
    UdpServer();
    ~UdpServer();

    bool listen(const QHostAddress &address, quint16 port);
    bool isListening() const;
    void close();

    bool write(const QByteArray &data);

signals:

    void errorMessage(const QString &message);
    void warningMessage(const QString &message);
    void infoMessage(const QString &message);

    void datagramReceived(const QString &peerInfo,
                          const QByteArray &plainText);

private slots:
    void readyRead();

private:
    void handleNewConnection(const QHostAddress &peerAddress, quint16 peerPort,
                             const QByteArray &clientHello);

    void doHandshake(QDtls *newConnection, const QByteArray &clientHello);
    void shutdown();

    QString peer_info(const QHostAddress &address, quint16 port);

    bool listening = false;
    QUdpSocket serverSocket;

    QHostAddress mHostAddress;
    quint16 mPort;

    Q_DISABLE_COPY(UdpServer)
};

#endif // UDPSERVER_H
