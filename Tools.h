#ifndef TOOLS_H
#define TOOLS_H

/**
 * @file Tools.h
 * @brief Declares the Tools class, which provides basic drawing functionality for the sprite editor.
 *
 * This class includes definitions for available tool types and color palettes,
 * along with static utility functions to apply drawing actions (pen, eraser, fill)
 * on a QImage-based canvas.
 *
 * @author Jason Chang (main)
 *
 * Checked by Arthur Mo, Kirra Kotsenburg
 */

#include <QImage>
#include <QColor>
#include <QPoint>

/**
 * @class Tools
 * @brief Static utility class providing drawing tool functionality.
 */
class Tools {
public:
    /**
     * @enum ToolType
     * @brief Tool types available in the sprite editor.
     */
    enum class ToolType {
        Pen,
        Eraser,
        Fill
    };

    /**
     * @enum ColorType
     * @brief Color palette for the sprite editor.
     */
    enum class ColorType {
        Black,
        White,
        Gray,
        Red,
        Meat,
        DarkBrown,
        Brown,
        Orange,
        Yellow,
        DarkGreen,
        Green,
        SlimeGreen,
        NightBlue,
        SeaBlue,
        SkyBlue,
        CloudBlue
    };

    /**
     * @brief Constructs a Tools object.
     */
    Tools();

    /**
     * @brief Converts a ColorType to a QColor.
     * @param colorType The ColorType to convert.
     * @return The corresponding QColor.
     */
    static QColor getQColor(ColorType colorType);

    /**
     * @brief Gets the color at the specified position.
     * @param image The image to sample from.
     * @param pos The position to sample at.
     * @return The color at the specified position.
     */
    static QColor getColorAt(const QImage& image, const QPoint& pos);

    /**
     * @brief Fills an area with a specified color using a BFS algorithm.
     * @param image The image to modify.
     * @param startPos The starting position for the fill.
     * @param fillColor The color to fill with.
     */
    static void fillArea(QImage& image, const QPoint& startPos, const QColor& fillColor);


    /**
     * @struct ToolResult
     * @brief Contains the result of applying a tool to an image.
     */
    struct ToolResult {
        QVector<QPoint> positions;  // The positions affected by the tool
        QVector<QColor> oldColors;  // The original colors at the affected positions
        QColor newColor;            // The new color applied
    };

    /**
     * @brief Applies the specified tool at the given position.
     * @param image The image to modify.
     * @param pos The position to apply the tool at.
     * @param toolType The type of tool to apply.
     * @param color The color to use with the tool.
     * @return A ToolResult containing information about the changes made.
     */
    static ToolResult applyTool(QImage& image, const QPoint& pos, ToolType toolType, const QColor& color);

    /**
     * @brief Gets the positions that would be filled by a fill operation.
     * @param image The image to analyze.
     * @param startPos The starting position for the fill.
     * @param targetColor The color to replace.
     * @return A vector of positions that would be filled.
     */
    static QVector<QPoint> getFillAreaPositions(const QImage& image, const QPoint& startPos, const QColor& targetColor);

private:
    static QMap<ToolType, Tools*> m_tools;
};

#endif // TOOLS_H
