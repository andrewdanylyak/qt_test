#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include <QObject>
#include <QThread>
#include <QtNetwork/QUdpSocket>

class SocketThread : public QObject
{
    Q_OBJECT

public:
    SocketThread(const QHostAddress &address, quint16 port, QObject *parent = nullptr);
    ~SocketThread();
    QThread m_thread;
signals:
    void dataReceived(const QByteArray &data);

private slots:
    void start();
    void readPendingDatagrams();

private:
    QHostAddress m_address;
    quint16 m_port;
    QUdpSocket *m_socket;

};

#endif // SOCKETTHREAD_H
