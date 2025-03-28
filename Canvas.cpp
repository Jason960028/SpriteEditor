/**
 * @file canvas.cpp
 * @brief Implements the Canvas class for rendering and interacting with pixel-based sprites.
 *
 * The Canvas class handles drawing the sprite image, rendering a checkerboard background for transparency,
 * displaying a pixel grid, and managing mouse input to emit signals for user interaction.
 *
 * @author Jason Chang
 */

#include "canvas.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>

Canvas::Canvas(QWidget* parent, SpriteEditorModel* model)
    : QWidget(parent),
    model(model)
{
    // Initialize with safe defaults
    canvasWidth = 32;
    canvasHeight = 32;
    maxGridWidth = 128;
    maxGridHeight = 128;

    if(model) {
        qDebug() << "Canvas created - Model is NOT NULL";
        canvasWidth = model->frameSize().width();
        canvasHeight = model->frameSize().height();
        maxGridWidth = model->getMaxSize().width();
        maxGridHeight = model->getMaxSize().height();
        displayImage = model->getCurrentFrame();

    } else {
        qDebug() << "Canvas created - Model is NULL!";
        displayImage = QImage(QSize(32, 32), QImage::Format_ARGB32);
        displayImage.fill(Qt::transparent);
    }

    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);

    // In Canvas constructor:
    qDebug() << "Canvas created - model:" << model
             << "size:" << canvasWidth << "x" << canvasHeight;
}

void Canvas::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    QPainter painter(this);

    // Draw checkerboard background for transparency visualization
    const int checkerSize = 8;

    for (int y = 0; y < height(); y += checkerSize) {
        for (int x = 0; x < width(); x += checkerSize) {
            QColor color = ((x / checkerSize + y / checkerSize) % 2 == 0)
            ? QColor(200, 200, 200)
            : QColor(255, 255, 255);
            painter.fillRect(x, y, checkerSize, checkerSize, color);
        }
    }

    // Calculate scaling to fit canvas to widget size
    qreal scaleX = static_cast<qreal>(width()) / canvasWidth;
    qreal scaleY = static_cast<qreal>(height()) / canvasHeight;
    qreal scale = qMin(scaleX, scaleY);

    // Calculate centering offset
    int offsetX = (width() - static_cast<int>(canvasWidth * scale)) / 2;
    int offsetY = (height() - static_cast<int>(canvasHeight * scale)) / 2;

    painter.translate(offsetX, offsetY);
    painter.scale(scale, scale);

    qDebug() << "current image painted";
    // Draw the current image
    painter.drawImage(QPoint(0, 0), displayImage);

    // Draw pixel grid for editing
    painter.setPen(QColor(100, 100, 100, 100));
    for (int x = 0; x <= canvasWidth; ++x) {
        painter.drawLine(x, 0, x, canvasHeight);
    }
    for (int y = 0; y <= canvasHeight; ++y) {
        painter.drawLine(0, y, canvasWidth, y);
    }
}

QPoint Canvas::screenToImagePos(const QPoint& screenPos) const {
    // Calculate scaling based on canvas size
    qreal scaleX = static_cast<qreal>(width()) / canvasWidth;
    qreal scaleY = static_cast<qreal>(height()) / canvasHeight;
    qreal scale = qMin(scaleX, scaleY);

    // Calculate offset for centering
    int offsetX = (width() - static_cast<int>(canvasWidth * scale)) / 2;
    int offsetY = (height() - static_cast<int>(canvasHeight * scale)) / 2;

    // Convert screen coordinates to image coordinates
    int imageX = static_cast<int>((screenPos.x() - offsetX) / scale);
    int imageY = static_cast<int>((screenPos.y() - offsetY) / scale);

    if (imageX >= 0 && imageX < canvasWidth && imageY >= 0 && imageY < canvasHeight) {
        return QPoint(imageX, imageY);
    }

    // Return (-1, -1) if outside image bounds
    return QPoint(-1, -1);
}

void Canvas::updateCanvas(const QImage& frameImage) {

    displayImage = frameImage;
    update();
}

void Canvas::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        QPoint pixelPos = screenToImagePos(event->pos());
        emit mousePressed(pixelPos);
    }
}

void Canvas::mouseMoveEvent(QMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton) {
        QPoint pixelPos = screenToImagePos(event->pos());
        emit mouseDragged(pixelPos);
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        QPoint pixelPos = screenToImagePos(event->pos());
        emit mouseReleased(pixelPos);
    }
}

