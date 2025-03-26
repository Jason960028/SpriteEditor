#include "Canvas.h"
#include <QPainter>
#include <QMouseEvent>

Canvas::Canvas(QWidget *parent)
    : QWidget(parent),
    isDrawing(false)
{
    // Initialize canvas with default size 32x32.
    image = QImage(32, 32, QImage::Format_ARGB32);
    image.fill(Qt::white);
}

QSize Canvas::minimumSizeHint() const
{
    return QSize(32, 32);
}

QSize Canvas::sizeHint() const
{
    // Return the current image size.
    return image.size();
}

void Canvas::setCanvasSize(int width, int height)
{
    //need logic to set minimum and maximum size

    image = QImage(width, height, QImage::Format_ARGB32);
    image.fill(Qt::white);
    update();
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // Scale the image to fill the widget's area.
    painter.drawImage(rect(), image, image.rect());
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isDrawing = true;
        QPoint pos = event->pos();
        // If scaling is applied, map widget coordinates to image coordinates.
        tool.applyTool(image, pos);
        update();
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if (isDrawing)
    {
        QPoint pos = event->pos();
        tool.applyTool(image, pos);
        update();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isDrawing = false;
    }
}
