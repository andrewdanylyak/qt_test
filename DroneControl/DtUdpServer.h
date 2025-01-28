#ifndef DTUDPSERVER_H
#define DTUDPSERVER_H

#include <QObject>
#include <QtNetwork>

class UdpServer : public QObject
{
    Q_OBJECT
public:
    UdpServer();
    ~ UdpServer();

    struct Config_t {
        QHostAddress listenAddress;
        quint16 listenPort;
        QHostAddress sendAddress;
        quint16 sendPort;
        Config_t& operator = (const Config_t &conf)
        {
            listenAddress = conf.listenAddress;
            listenPort = conf.listenPort;
            sendAddress = conf.sendAddress;
            sendPort = conf.sendPort;
            return *this;
        }
    };

    bool run (const Config_t &config);
    bool isListening() const;
    void close();
    bool write(const QByteArray &data);

signals:
    void errorMessage(const QString &message);
    void warningMessage(const QString &message);
    void infoMessage(const QString &message);
    void dataReceived(const QByteArray &data);

private slots:
    void readyRead();
private:
    Config_t mConfig {};
    bool listening = false;
    QUdpSocket serverSocket {};
    void shutdown();
};

#endif // DTUDPSERVER_H
