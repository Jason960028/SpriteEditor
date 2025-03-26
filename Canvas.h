#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QImage>
#include "tools.h"

/**
 * @brief The Canvas class implements the sprite editor canvas.
 *
 * This widget handles user mouse events to modify a QImage representing the sprite.
 */
class Canvas : public QWidget {
    Q_OBJECT

    public:

        /**
         * @brief Constructs a CanvasWidget with an optional parent widget.
         * @param parent Pointer to the parent widget.
         */
        explicit Canvas(QWidget *parent = nullptr);

        /**
         * @brief Provides a minimum size hint for the canvas.
         * @return The minimum size.
         */
        QSize minimumSizeHint() const override;

        /**
         * @brief Provides a recommended size for the canvas.
         * @return The recommended size.
         */
        QSize sizeHint() const override;

        /**
         * @brief Sets the canvas size.
         * @param width Width of the canvas (allowed between 32 and 64).
         * @param height Height of the canvas (allowed between 32 and 64).
         */
        void setCanvasSize(int width, int height);

    protected:

        /**
         * @brief Paint event to render the canvas.
         * @param event Pointer to the paint event.
         */
        void paintEvent(QPaintEvent *event) override;

        /**
         * @brief Mouse press event handler.
         * @param event Pointer to the mouse event.
         */
        void mousePressEvent(QMouseEvent *event) override;

        /**
         * @brief Mouse move event handler.
         * @param event Pointer to the mouse event.
         */
        void mouseMoveEvent(QMouseEvent *event) override;

        /**
         * @brief Mouse release event handler.
         * @param event Pointer to the mouse event.
         */
        void mouseReleaseEvent(QMouseEvent *event) override;

    private:

        QImage image;         ///< The sprite image.
        bool isDrawing;       ///< Indicates if a drawing operation is in progress.
        Tools tool;           ///< Instance of drawing tools.
};

#endif // CANVAS_H
