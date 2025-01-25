#include "socketthread.h"

#include <QDebug>

SocketThread::SocketThread(const QHostAddress &address, quint16 port, QObject *parent)
    : QObject(parent), m_address(address), m_port(port), m_socket(nullptr)
{
    connect(&m_thread, &QThread::started, this, &SocketThread::start);
    moveToThread(&m_thread);
    m_thread.start();
}

SocketThread::~SocketThread()
{
    m_thread.quit();
    m_thread.wait();
    if (m_socket) {
        m_socket->close();
        delete m_socket;
    }

}

void SocketThread::start()
{
    m_socket = new QUdpSocket();
    m_socket->bind(m_address, m_port);
    connect(m_socket, &QUdpSocket::readyRead, this, &SocketThread::readPendingDatagrams);
}

void SocketThread::readPendingDatagrams()
{
    while (m_socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(m_socket->pendingDatagramSize());
        m_socket->readDatagram(datagram.data(), datagram.size(), &m_address, &m_port);
        qDebug("Data recived");
        //emit dataReceived(datagram);
    }
}
