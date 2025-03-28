#ifndef TOOLS_H
#define TOOLS_H

/**
 * @file tools.h
 * @brief Declares the Tools class, which provides basic drawing functionality for the sprite editor.
 *
 * This class includes definitions for available tool types and color palettes,
 * along with static utility functions to apply drawing actions (pen, eraser, fill)
 * on a QImage-based canvas.
 *
 *
 * @author Jason Chang
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
     * @brief Applies a tool at a specific position.
     * @param image The image to modify.
     * @param pos The position to apply the tool.
     * @param toolType The tool to use.
     * @param colorType The color to use (ignored for Eraser).
     */
    static void applyTool(QImage& image, const QPoint& pos, ToolType toolType, const QColor& color);

    /**
     * @brief Gets the color at the specified position.
     * @param image The image to sample from.
     * @param pos The position to sample at.
     * @return The color at the specified position.
     */
    static QColor getColorAt(const QImage& image, const QPoint& pos);

    /**
     * @brief Fills an area with a specified color using a flood-fill algorithm.
     * @param image The image to modify.
     * @param startPos The starting position for the fill.
     * @param fillColor The color to fill with.
     */
    static void fillArea(QImage& image, const QPoint& startPos, const QColor& fillColor);

private:
    static QMap<ToolType, Tools*> m_tools;


};

#endif // TOOLS_H
