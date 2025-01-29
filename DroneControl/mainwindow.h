#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "DtParser.h"
#include "DtVideoWidget.h"

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
    void onPushButtonClicked();
    void onSettingsClicked();

signals:
    void stopAll();
private:
    Ui::MainWindow *ui;
    Parser parser;
    QString videoPath;
    QThread mThread;
    void stopThreads();
    Dt::VideoWidget mVideoWidget;

    void setupSlots();
};
#endif // MAINWINDOW_H
