#ifndef CANVAS_H
#define CANVAS_H

/**
 * @file Canvas.h
 * @brief Declares the Canvas class responsible for displaying and interacting with pixel-based sprites.
 *
 * The Canvas class provides a QWidget-based drawable surface for editing sprites.
 * It supports mouse interaction, zoom-scaling, grid rendering, and updating pixel images with external frame data.
 *
 * @author Jason Chang (main), Arthur Mo (Adjustments for redo/undo, Canvas Resizing)
 *
 * Checked by Arthur Mo, Kirra Kostenburg
 */

#include <QWidget>
#include <QImage>
#include <QVector>
#include <QColor>
#include "spriteEditorModel.h"

/**
 * @class Canvas
 * @brief A QWidget that provides pixel-level editing for sprite images.
 */
class Canvas : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructor for the Canvas object.
     * @param parent The parent QWidget.
     * @param model The sprite editor model.
     */
    explicit Canvas(QWidget* parent = nullptr, SpriteEditorModel* model = nullptr);

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

    /**
     * @brief Resets the canvas size based on the model's current frame size.
     */
    void resetCanvasSize();

    /**
     * @brief Gets the canvas width.
     * @return The width of the canvas.
     */
    int getCanvasWidth() const { return canvasWidth; }

    /**
     * @brief Gets the canvas height.
     * @return The height of the canvas.
     */
    int getCanvasHeight() const { return canvasHeight; }

    /**
     * @brief Gets the maximum grid width.
     * @return The maximum width of the grid.
     */
    int getMaxGridWidth() const { return maxGridWidth; }

    /**
     * @brief Gets the maximum grid height.
     * @return The maximum height of the grid.
     */
    int getMaxGridHeight() const { return maxGridHeight; }

signals:
    /**
     * @brief Signal emitted when mouse is pressed on the canvas.
     * @param pos The position where the mouse was pressed.
     */
    void mousePressed(const QPoint& pos);

    /**
     * @brief Signal emitted when mouse is dragged on the canvas.
     * @param pos The current position of the mouse.
     */
    void mouseDragged(const QPoint& pos);

    /**
     * @brief Signal emitted when mouse is released on the canvas.
     * @param pos The position where the mouse was released.
     */
    void mouseReleased(const QPoint& pos);

protected:
    /**
     * @brief Handles paint events for the canvas.
     * @param event The paint event.
     */
    void paintEvent(QPaintEvent* event) override;

    /**
     * @brief Handles mouse press events.
     * @param event The mouse event.
     */
    void mousePressEvent(QMouseEvent* event) override;

    /**
     * @brief Handles mouse move events.
     * @param event The mouse event.
     */
    void mouseMoveEvent(QMouseEvent* event) override;

    /**
     * @brief Handles mouse release events.
     * @param event The mouse event.
     */
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    static const int MIN_CANVAS_SIZE = 32;

    QImage displayImage;
    int canvasWidth;
    int canvasHeight;
    int maxGridWidth;
    int maxGridHeight;
    SpriteEditorModel* model;

    bool m_isDrawing = false; // Indicator for press and drag
    QPoint m_lastPos;
    QVector<QPoint> m_modifiedPixels;
    QVector<QColor> m_oldColors;
    QColor m_newColor;
};

#endif // CANVAS_H
