#ifndef CANVAS_H
#define CANVAS_H

/**
 * @file canvas.h
 * @brief Declares the Canvas class responsible for displaying and interacting with pixel-based sprites.
 *
 * The Canvas class provides a QWidget-based drawable surface for editing sprites. It supports mouse interaction,
 * zoom-scaling, grid rendering, and updating pixel images with external frame data.
 *
 * @author Jason Chang
 */

#include <QWidget>
#include <QImage>
#include <QVector>
#include <QColor>
#include "SpriteEditorModel.h"

/**
 * @class Canvas
 * @brief A QWidget that provides pixel-level editing for sprite images.
 */
class Canvas : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs a Canvas object.
     * @param parent The parent QWidget (default is nullptr).
     */
    explicit Canvas( QWidget* parent = nullptr, SpriteEditorModel* model = nullptr);

    /**
     * @brief Updates the displayed image on the canvas.
     * @param frameImage The new frame image to render.
     */
    void updateCanvas(const QImage& frameImage);

    /**
     * @brief Converts screen coordinates to image pixel coordinates.
     * @param screenPos The position on the screen.
     * @return The corresponding image position, or (-1, -1) if out of bounds.
     */
    QPoint screenToImagePos(const QPoint& screenPos) const;

    // Accessors for canvas properties
    int getCanvasWidth() const { return canvasWidth; }
    int getCanvasHeight() const { return canvasHeight; }
    int getMaxGridWidth() const { return maxGridWidth; }
    int getMaxGridHeight() const { return maxGridHeight; }

signals:
    void mousePressed(const QPoint& pos);
    void mouseDragged(const QPoint& pos);
    void mouseReleased(const QPoint& pos);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    static const int MIN_CANVAS_SIZE = 32;

    QImage displayImage;
    int canvasWidth;
    int canvasHeight;
    int maxGridWidth;
    int maxGridHeight;
    SpriteEditorModel* model;
};

#endif // CANVAS_H
