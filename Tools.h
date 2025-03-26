#ifndef TOOLS_H
#define TOOLS_H

#include <QWidget>
#include <QImage>
#include <QMouseEvent>
#include <QRect>
#include <QColor>
#include <QPoint>

/**
 * @brief The Tools class provides drawing operations for the sprite editor.
 */
class Tools {

public:
    /**
     * @brief Enumeration for tool types.
     */
    enum class TOOL_TYPE {
        PEN,
        ERASER,
        FILL
    };

    /**
     * @brief Enumeration for color types.
     */
    enum class COLOR_TYPE {
        BLACK,
        WHITE,
        GRAY,
        RED,
        MEAT,
        DARK_BROWN,
        BROWN,
        ORANGE,
        YELLOW,
        DARK_GREEN,
        GREEN,
        SLIME_GREEN,
        NIGHT_BLUE,
        SEA_BLUE,
        SKY_BLUE,
        CLOUD_BLUE
    };

    /**
     * @brief Constructs a Tools object with default settings.
     */
    Tools();

    /**
     * @brief Select a drawing tool.
     * @param tool The tool type to select.
     */
    void selectTool(TOOL_TYPE tool);

    /**
     * @brief Returns the currently selected tool.
     * @return The current tool type.
     */
    TOOL_TYPE currentTool() const;

    /**
     * @brief Set the current drawing color.
     * @param color The color type.
     */
    void setColor(COLOR_TYPE color);

    /**
     * @brief Returns the current drawing color.
     * @return The current color type.
     */
    COLOR_TYPE currentColor() const;

    /**
     * @brief Converts a COLOR_TYPE to a QColor.
     * @param color The color type.
     * @return The corresponding QColor.
     */
    static QColor toQColor(COLOR_TYPE color);

    /**
     * @brief Applies the current tool to the given image at a specified positionition.
     * @param image The image to modify.
     * @param position The positionition where the tool is applied.
     */
    void applyTool(QImage &image, const QPoint &position);

    /**
     * @brief Sets the brush size for the pen tool.
     * @param size Brush size (allowed values: 1 to 9).
     */
    void setPenSize(int size);

    /**
     * @brief Returns the current brush size for the pen tool.
     * @return The pen brush size.
     */
    int penSize() const;

    /**
     * @brief Sets the brush size for the eraser tool.
     * @param size Brush size (allowed values: 1 to 9).
     */
    void setEraserSize(int size);

    /**
     * @brief Returns the current brush size for the eraser tool.
     * @return The eraser brush size.
     */
    int eraserSize() const;

private:
    TOOL_TYPE m_currentTool;      ///< Currently selected drawing tool.
    COLOR_TYPE m_currentColor;    ///< Currently selected drawing color.
    int m_penSize;                ///< Brush size for the pen tool.
    int m_eraserSize;             ///< Brush size for the eraser tool.

    /**
     * @brief Applies the pen tool to the image.
     * @param image The image to modify.
     * @param positionition The positionitionition to draw.
     */
    void applyPen(QImage &image, const QPoint &position);

    /**
     * @brief Applies the eraser tool to the image.
     * @param image The image to modify.
     * @param position The positionition to erase.
     */
    void applyEraser(QImage &image, const QPoint &position);

    /**
     * @brief Applies the fill tool to the image.
     * @param image The image to modify.
     * @param position The starting positionition for fill.
     */
    void applyFill(QImage &image, const QPoint &position);
};

#endif // TOOLS_H
