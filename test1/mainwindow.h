#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "udpserver.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addErrorMessage(const QString &message);
    void addWarningMessage(const QString &message);
    void addInfoMessage(const QString &message);
    void addClientMessage(const QString &peerInfo,
                          const QByteArray &plainText);
    void on_mOpenButton_clicked();
    void on_mCloseButton_clicked();
    void on_mWriteButton_clicked();
private:
    Ui::MainWindow *ui;
    UdpServer orinPodServer;
    //UdpServer orinServer2;
    QHostAddress address;
    quint16 orinPodPort;
    void updateUi();
};
#endif // MAINWINDOW_H
