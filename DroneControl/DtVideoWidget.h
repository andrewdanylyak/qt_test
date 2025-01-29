#ifndef DTVIDEOWIDGET_H
#define DTVIDEOWIDGET_H

#include <QWidget>
#include <gst/gst.h>
#include <gst/video/videooverlay.h>

namespace Dt
{
class VideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = nullptr);
    ~VideoWidget();

    void playStream(const QString &url);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    GstElement *m_pipeline;
    static void on_pad_added(GstElement *src, GstPad *new_pad, gpointer data);
};
}

#endif // DTVIDEOWIDGET_H

