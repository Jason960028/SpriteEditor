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
#include "RedoUndo.h"
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
    maxGridWidth = 64;
    maxGridHeight = 64;

    if(model) {
        qDebug() << "Canvas created - Model is NOT NULL";
        canvasWidth = model->getFrameSize().width();
        canvasHeight = model->getFrameSize().height();
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

    if(model) {
        displayImage = model->getCurrentFrame(); // Refresh image reference
    }

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

    imageX = qBound(0, imageX, canvasWidth - 1);
    imageY = qBound(0, imageY, canvasHeight - 1);

    // Return (-1, -1) if outside image bounds
    return QPoint(imageX, imageY);
}

void Canvas::updateCanvas(const QImage& frameImage) {

    displayImage = frameImage;
    update();
}

void Canvas::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        m_isDrawing = true;
        QPoint pixelPos = screenToImagePos(event->pos());
        m_lastPos = pixelPos;
        m_modifiedPixels.clear();
        m_oldColors.clear();
        m_newColor = model->getCurrentColor();

        // Record first pixel
        QImage& frame = model->getCurrentFrame();
        m_oldColors.append(frame.pixelColor(pixelPos));
        m_modifiedPixels.append(pixelPos);
        emit mousePressed(pixelPos);
    }
}

void Canvas::mouseMoveEvent(QMouseEvent* event) {
    if ((event->buttons() & Qt::LeftButton) && m_isDrawing) {
        QPoint pixelPos = screenToImagePos(event->pos());
        if (pixelPos != m_lastPos) {
            QImage& frame = model->getCurrentFrame();

            // Record pixel only if it's new
            if (!m_modifiedPixels.contains(pixelPos)) {
                m_oldColors.append(frame.pixelColor(pixelPos));
                m_modifiedPixels.append(pixelPos);
            }

            emit mouseDragged(pixelPos);
            m_lastPos = pixelPos;
        }
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent* event) {
    if(event->button() == Qt::LeftButton && m_isDrawing) {
        m_isDrawing = false;

        if(!m_modifiedPixels.isEmpty() && model && model->currentUndoStack()) {
            model->currentUndoStack()->push(
                new RedoUndoCommand(
                    model,
                    m_modifiedPixels,
                    m_oldColors,
                    m_newColor,
                    model->getCurrentIndex())
                );
        }

        emit mouseReleased(screenToImagePos(event->pos()));
    }
}

void Canvas::resetCanvasSize()
{
    if(model) {
        canvasWidth = model->getFrameSize().width();
        canvasHeight = model->getFrameSize().height();
        maxGridWidth = model->getMaxSize().width();
        maxGridHeight = model->getMaxSize().height();
        displayImage = model->getCurrentFrame();
        update();
    } else {
        displayImage = QImage(QSize(32, 32), QImage::Format_ARGB32);
        displayImage.fill(Qt::transparent);
    }
}

