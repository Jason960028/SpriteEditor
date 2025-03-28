#include "Tools.h"
#include <QPainter>
#include "SpriteEditorModel.h"


// Static tool instances
QMap<Tools::ToolType, Tools*> Tools::m_tools;
/**
 * @file tools.cpp
 * @brief Implements the Tools class, providing core drawing tool logic for the sprite editor.
 *
 * This file includes the implementation of pixel-editing tools such as Pen, Eraser,
 * and Fill, as well as utility functions to convert tool-specific types to Qt types.
 * The fill tool uses a breadth-first flood fill algorithm.
 *
 * @author Jason Chang
 */

#include "Tools.h"
#include <QQueue>
#include <QSet>

Tools::Tools() {


}

QColor Tools::getQColor(ColorType colorType) {
    switch (colorType) {
    case ColorType::Black:       return QColor(0, 0, 0);
    case ColorType::White:       return QColor(255, 255, 255);
    case ColorType::Gray:        return QColor(128, 128, 128);
    case ColorType::Red:         return QColor(255, 0, 0);
    case ColorType::Meat:        return QColor(255, 150, 150);
    case ColorType::DarkBrown:   return QColor(101, 67, 33);
    case ColorType::Brown:       return QColor(150, 100, 50);
    case ColorType::Orange:      return QColor(255, 165, 0);
    case ColorType::Yellow:      return QColor(255, 255, 0);
    case ColorType::DarkGreen:   return QColor(0, 100, 0);
    case ColorType::Green:       return QColor(0, 255, 0);
    case ColorType::SlimeGreen:  return QColor(50, 205, 50);
    case ColorType::NightBlue:   return QColor(25, 25, 112);
    case ColorType::SeaBlue:     return QColor(0, 105, 148);
    case ColorType::SkyBlue:     return QColor(135, 206, 235);
    case ColorType::CloudBlue:   return QColor(200, 230, 255);
    default:                     return QColor(0, 0, 0);
    }
}

void Tools::applyTool(QImage& image, const QPoint& pos, ToolType toolType, const QColor& color) {
    // Check if position is within image bounds
    if (pos.x() < 0 || pos.x() >= image.width() ||
        pos.y() < 0 || pos.y() >= image.height()) {
        return;
    }

    switch (toolType) {
    case ToolType::Pen:
        image.setPixelColor(pos, color);
        break;
    case ToolType::Eraser:
        image.setPixelColor(pos, Qt::transparent);
        break;
    case ToolType::Fill:
        fillArea(image, pos, color);
        break;
    }
}

QColor Tools::getColorAt(const QImage& image, const QPoint& pos) {
    if (pos.x() >= 0 && pos.x() < image.width() &&
        pos.y() >= 0 && pos.y() < image.height()) {
        return image.pixelColor(pos);
    }
    return Qt::transparent;
}

void Tools::fillArea(QImage& image, const QPoint& startPos, const QColor& fillColor) {
    // Get the color at the starting position — this is the target color to be replaced
    QColor targetColor = image.pixelColor(startPos);

    // If the target color is the same as the fill color, there's nothing to do
    if (targetColor == fillColor) {
        return;
    }

    // Use BFS (Breadth-First Search) approach with a queue for filling
    QQueue<QPoint> queue;     // Queue to manage pixels to process
    QSet<QPoint> visited;     // Set to track already-visited positions and prevent infinite loops

    // Start from the initial pixel
    queue.enqueue(startPos);
    visited.insert(startPos);

    // Direction vectors for 4-connected neighbors (up, right, down, left)
    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};

    // Process the queue until all connected targetColor pixels are filled
    while (!queue.isEmpty()) {
        QPoint current = queue.dequeue();

        // Fill the current pixel with the new color
        image.setPixelColor(current, fillColor);

        // Check all 4 neighboring pixels
        for (int i = 0; i < 4; ++i) {
            QPoint next(current.x() + dx[i], current.y() + dy[i]);

            // Skip if next point is out of bounds
            if (next.x() < 0 || next.x() >= image.width() ||
                next.y() < 0 || next.y() >= image.height()) {
                continue;
            }

            // Skip if already visited or the color does not match the target
            if (visited.contains(next)) {
                continue;
            }

            if (image.pixelColor(next) == targetColor) {
                queue.enqueue(next);        // Add to queue for processing
                visited.insert(next);       // Mark as visited
            }
        }
    }
}
