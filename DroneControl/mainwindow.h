#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// #include <QVideoWidget>
// #include <QMediaPlayer>

// #include <QUrl>
// #include <QNetworkRequest>
// #include <QProcess>
#include <QMainWindow>

// #include <gst/gst.h>
// #include <gst/video/videooverlay.h>

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

    // QVideoWidget * videoWidget;

    // QMediaPlayer * player0;

    // QUrl url0;
    // QNetworkRequest requestRtsp0;
    // bool is_connected = false;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addErrorMessage(const QString &message);
    void addWarningMessage(const QString &message);
    void addInfoMessage(const QString &message);
    void on_mSettingsButton_clicked();
    void on_pushButton_clicked();

signals:
    void stopAll();
private:
    Ui::MainWindow *ui;
    Parser parser;
    QString videoPath;
    QThread mThread;
    void stopThreads();
    Dt::VideoWidget mVideoWidget;
    // GstElement *m_pipeline = nullptr;
    // void PlayVideoStream(guintptr output, const QString &url);
    // static void on_pad_added(GstElement *src, GstPad *new_pad, gpointer data);
};
#endif // MAINWINDOW_H
