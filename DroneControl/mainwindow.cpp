#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "appsetupdialog.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    //, m_pipeline(nullptr)
{
    ui->setupUi(this);
    connect(&parser, &Parser::errorMessage, this, &MainWindow::addErrorMessage);
    connect(&parser, &Parser::warningMessage, this, &MainWindow::addWarningMessage);
    connect(&parser, &Parser::infoMessage, this, &MainWindow::addInfoMessage);

    // url0 = "rtsp://192.168.144.21:8554/test";
    // gst_init(nullptr, nullptr);
    // ui->widgetVideo->setAttribute(Qt::WA_NativeWindow);
    QString url1 = "rtsp://192.168.144.21:8554/test";
    ui->gridLayout->addWidget(&mVideoWidget);
    mVideoWidget.resize(800, 600);
    mVideoWidget.playStream(url1);
    // PlayVideoStream((guintptr)ui->widgetVideo->winId(), url1);
}

MainWindow::~MainWindow()
{
    // if (m_pipeline) {
    //     gst_element_set_state(m_pipeline, GST_STATE_NULL);
    //     gst_object_unref(m_pipeline);
    // }
    stopThreads();
    delete ui;
}

// void MainWindow::PlayVideoStream(guintptr output, const QString &url)
// {
//     if (m_pipeline) {
//         gst_element_set_state(m_pipeline, GST_STATE_NULL);
//         gst_object_unref(m_pipeline);
//         m_pipeline = nullptr;
//     }

//     // Створюємо новий конвеєр
//     m_pipeline = gst_pipeline_new("video-pipeline");

//     if (!m_pipeline) {
//         qWarning("Не вдалося створити конвеєр GStreamer.");
//         return;
//     }

//     // Створюємо елементи конвеєра
//     GstElement *source = gst_element_factory_make("rtspsrc", "source");
//     GstElement *queue = gst_element_factory_make("queue", "queue");
//     GstElement *depay = gst_element_factory_make("rtph264depay", "depay");
//     GstElement *decoder = gst_element_factory_make("avdec_h264", "decoder");
//     GstElement *conv = gst_element_factory_make("videoconvert", "conv");
//     GstElement *sink = gst_element_factory_make("xvimagesink", "videosink");

//     if (!source || !queue || !depay || !decoder || !conv || !sink) {
//         qWarning("Не вдалося створити один або більше елементів конвеєра.");
//         return;
//     }

//     // Додаємо елементи до конвеєра
//     gst_bin_add_many(GST_BIN(m_pipeline), source, queue, depay, decoder, conv, sink, nullptr);

//     // З'єднуємо елементи
//     if (!gst_element_link_many(queue, depay, decoder, conv, sink, nullptr)) {
//         qWarning("Не вдалося з'єднати елементи.");
//         return;
//     }

//     // Налаштовуємо RTSP джерело
//     g_object_set(source, "location", url.toUtf8().constData(), nullptr);
//     g_object_set(source, "buffer-mode", 0, nullptr);  // Використання режиму буферизації
//     g_object_set(source, "latency", 250, nullptr);  // Збільшення затримки для більшої буферизації
//     g_object_set(source, "buffer-size", 1048576, nullptr);  // Встановлення розміру буфера (1MB)

//     // Налаштовуємо елемент queue
//     g_object_set(queue, "max-size-buffers", 1000, nullptr);  // Максимальна кількість буферів
//     g_object_set(queue, "max-size-time", 2000000000, nullptr);  // Максимальний час буферизації (2 секунди)
//     g_object_set(queue, "max-size-bytes", 1048576, nullptr);  // Максимальний розмір буфера (1MB)

//     g_object_set(sink, "sync", FALSE, nullptr);

//     // Налаштовуємо сигнал для depayloader
//     g_signal_connect(source, "pad-added", G_CALLBACK(on_pad_added), queue);

//     // Приводимо відео-синк до GstVideoOverlay
//     GstVideoOverlay *overlay = GST_VIDEO_OVERLAY(sink);
//     if (!overlay) {
//         qWarning("Відео-синк не реалізує GstVideoOverlay.");
//         return;
//     }

//     gst_video_overlay_set_window_handle(overlay, output);

//     gst_element_set_state(m_pipeline, GST_STATE_PLAYING);
// }

// void MainWindow::on_pad_added(GstElement *src, GstPad *new_pad, gpointer data)
// {
//     GstPad *sink_pad = gst_element_get_static_pad(GST_ELEMENT(data), "sink");
//     if (gst_pad_is_linked(sink_pad)) {
//         gst_object_unref(sink_pad);
//         return;
//     }

//     GstCaps *new_pad_caps = gst_pad_get_current_caps(new_pad);
//     const GstStructure *new_pad_struct = gst_caps_get_structure(new_pad_caps, 0);
//     const gchar *new_pad_type = gst_structure_get_name(new_pad_struct);

//     if (g_str_has_prefix(new_pad_type, "application/x-rtp")) {
//         gst_pad_link(new_pad, sink_pad);
//     }

//     if (new_pad_caps != nullptr)
//         gst_caps_unref(new_pad_caps);

//     gst_object_unref(sink_pad);
// }

void MainWindow::on_mSettingsButton_clicked()
{
    AppSetupDialog appSetupDialog;
    UdpServer::Config_t config {};
    if (appSetupDialog.exec() == QDialog::Accepted) {
        config.listenAddress = appSetupDialog.orinRxIp();
        config.listenPort = appSetupDialog.orinRxPort();
        config.sendAddress = appSetupDialog.orinTxIp();
        config.sendPort = appSetupDialog.orinTxPort();
        videoPath = appSetupDialog.videoPath();
        parser.config(config);

        parser.moveToThread(&mThread);
        connect(&mThread, &QThread::started, &parser, &Parser::process);
        connect(&parser, &Parser::finished, &mThread, &QThread::quit);
        connect(this, &MainWindow::stopAll, &parser, &Parser::stop);
        connect(&parser, &Parser::finished, &parser, &Parser::deleteLater);
        connect(&mThread, &QThread::finished, &mThread, &QThread::deleteLater);
        mThread.start();
    }

}

void MainWindow::stopThreads()
{
    emit stopAll();
}


void MainWindow::on_pushButton_clicked()
{
    parser.cmdGetStatus();
}

void MainWindow::addErrorMessage(const QString &message)
{

    qDebug("%s", qPrintable(message));
}

void MainWindow::addWarningMessage(const QString &message)
{
    qDebug("%s", qPrintable(message));
}

void MainWindow::addInfoMessage(const QString &message)
{
    qDebug("%s", qPrintable(message));
}

