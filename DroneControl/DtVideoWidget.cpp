#include "DtVideoWidget.h"
#include <QDebug>

using namespace Dt;

VideoWidget::VideoWidget(QWidget *parent)
    : QWidget(parent), m_pipeline(nullptr)
{
    gst_init(nullptr, nullptr);
    setAttribute(Qt::WA_NativeWindow);
}

VideoWidget::~VideoWidget()
{
    if (m_pipeline) {
        gst_element_set_state(m_pipeline, GST_STATE_NULL);
        gst_object_unref(m_pipeline);
    }
}

void VideoWidget::playStream(const QString &url)
{
    // Зупиняємо та звільняємо попередній конвеєр, якщо він існує
    if (m_pipeline) {
        gst_element_set_state(m_pipeline, GST_STATE_NULL);
        gst_object_unref(m_pipeline);
        m_pipeline = nullptr;
    }

    // Створюємо новий конвеєр
    m_pipeline = gst_pipeline_new("video-pipeline");

    if (!m_pipeline) {
        qWarning("Не вдалося створити конвеєр GStreamer.");
        return;
    }

    // Створюємо елементи конвеєра
    GstElement *source = gst_element_factory_make("rtspsrc", "source");
    GstElement *queue = gst_element_factory_make("queue", "queue");
    GstElement *depay = gst_element_factory_make("rtph264depay", "depay");
    GstElement *decoder = gst_element_factory_make("avdec_h264", "decoder");
    GstElement *conv = gst_element_factory_make("videoconvert", "conv");
    GstElement *sink = gst_element_factory_make("xvimagesink", "videosink");

    if (!source || !queue || !depay || !decoder || !conv || !sink) {
        qWarning("Не вдалося створити один або більше елементів конвеєра.");
        return;
    }

    // Додаємо елементи до конвеєра
    gst_bin_add_many(GST_BIN(m_pipeline), source, queue, depay, decoder, conv, sink, nullptr);

    // З'єднуємо елементи
    if (!gst_element_link_many(queue, depay, decoder, conv, sink, nullptr)) {
        qWarning("Не вдалося з'єднати елементи.");
        return;
    }

    // Налаштовуємо RTSP джерело
    g_object_set(source, "location", url.toUtf8().constData(), nullptr);
    g_object_set(source, "buffer-mode", 0, nullptr);  // Використання режиму буферизації
    g_object_set(source, "latency", 250, nullptr);  // Збільшення затримки для більшої буферизації
    g_object_set(source, "buffer-size", 1048576, nullptr);  // Встановлення розміру буфера (1MB)

    // Налаштовуємо елемент queue
    g_object_set(queue, "max-size-buffers", 1000, nullptr);  // Максимальна кількість буферів
    g_object_set(queue, "max-size-time", 2000000000, nullptr);  // Максимальний час буферизації (2 секунди)
    g_object_set(queue, "max-size-bytes", 1048576, nullptr);  // Максимальний розмір буфера (1MB)

    g_object_set(sink, "sync", FALSE, nullptr);

    // Налаштовуємо сигнал для depayloader
    g_signal_connect(source, "pad-added", G_CALLBACK(on_pad_added), queue);

    // Приводимо відео-синк до GstVideoOverlay
    GstVideoOverlay *overlay = GST_VIDEO_OVERLAY(sink);
    if (!overlay) {
        qWarning("Відео-синк не реалізує GstVideoOverlay.");
        return;
    }

    // Встановлюємо вікно для відображення відео
    gst_video_overlay_set_window_handle(overlay, (guintptr)winId());

    // Запускаємо конвеєр
    gst_element_set_state(m_pipeline, GST_STATE_PLAYING);
}

void VideoWidget::on_pad_added(GstElement *src, GstPad *new_pad, gpointer data)
{
    GstPad *sink_pad = gst_element_get_static_pad(GST_ELEMENT(data), "sink");
    if (gst_pad_is_linked(sink_pad)) {
        gst_object_unref(sink_pad);
        return;
    }

    GstCaps *new_pad_caps = gst_pad_get_current_caps(new_pad);
    const GstStructure *new_pad_struct = gst_caps_get_structure(new_pad_caps, 0);
    const gchar *new_pad_type = gst_structure_get_name(new_pad_struct);

    if (g_str_has_prefix(new_pad_type, "application/x-rtp")) {
        gst_pad_link(new_pad, sink_pad);
    }

    if (new_pad_caps != nullptr)
        gst_caps_unref(new_pad_caps);

    gst_object_unref(sink_pad);
}

void VideoWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    if (m_pipeline) {
        GstElement *videoSink = nullptr;
        g_object_get(m_pipeline, "video-sink", &videoSink, nullptr);

        if (videoSink) {
            GstVideoOverlay *overlay = GST_VIDEO_OVERLAY(videoSink);
            gst_video_overlay_expose(overlay);
            gst_video_overlay_set_render_rectangle(overlay, 0, 0, width(), height());
            gst_object_unref(videoSink);
        }
    }
}

