#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DtUdpServer.h"
#include "DtParser.h"

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
    void on_mSettingsButton_clicked();
    void on_pushButton_clicked();
private:
    Ui::MainWindow *ui;
    Parser parser;
    QString videoPath;
};
#endif // MAINWINDOW_H
