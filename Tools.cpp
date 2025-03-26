#include "tools.h"
#include <QPainter>
#include <QStack>

Tools::Tools() : m_currentTool(TOOL_TYPE::PEN),
                 m_currentColor(COLOR_TYPE::BLACK),
                 m_penSize(1),
                 m_eraserSize(1) {
}

void Tools::selectTool(TOOL_TYPE tool) {
    m_currentTool = tool;
}

Tools::TOOL_TYPE Tools::currentTool() const {
    return m_currentTool;
}

void Tools::setColor(COLOR_TYPE color) {
    m_currentColor = color;
}

Tools::COLOR_TYPE Tools::currentColor() const {
    return m_currentColor;
}

QColor Tools::toQColor(COLOR_TYPE color) {
    switch (color) {
        case COLOR_TYPE::BLACK:       return QColor(Qt::black);
        case COLOR_TYPE::WHITE:       return QColor(Qt::white);
        case COLOR_TYPE::GRAY:        return QColor(Qt::gray);
        case COLOR_TYPE::RED:         return QColor(Qt::red);
        case COLOR_TYPE::MEAT:        return QColor(255, 102, 102);
        case COLOR_TYPE::DARK_BROWN:  return QColor(101, 67, 33);
        case COLOR_TYPE::BROWN:       return QColor(150, 75, 0);
        case COLOR_TYPE::ORANGE:      return QColor(255, 165, 0);
        case COLOR_TYPE::YELLOW:      return QColor(Qt::yellow);
        case COLOR_TYPE::DARK_GREEN:  return QColor(0, 100, 0);
        case COLOR_TYPE::GREEN:       return QColor(Qt::green);
        case COLOR_TYPE::SLIME_GREEN: return QColor(50, 205, 50);
        case COLOR_TYPE::NIGHT_BLUE:  return QColor(25, 25, 112);
        case COLOR_TYPE::SEA_BLUE:    return QColor(70, 130, 180);
        case COLOR_TYPE::SKY_BLUE:    return QColor(135, 206, 235);
        case COLOR_TYPE::CLOUD_BLUE:  return QColor(176, 196, 222);
        default:                      return QColor(Qt::black);
    }
}

void Tools::applyTool(QImage &image, const QPoint &position) {
    switch (m_currentTool) {
        case TOOL_TYPE::PEN:
            applyPen(image, position);
            break;
        case TOOL_TYPE::ERASER:
            applyEraser(image, position);
            break;
        case TOOL_TYPE::FILL:
            applyFill(image, position);
            break;
    }
}

void Tools::applyPen(QImage &image, const QPoint &position) {
    int halfSize = m_penSize / 2;
    QColor drawColor = toQColor(m_currentColor);

    for (int offsetY = -halfSize; offsetY <= halfSize; ++offsetY) {

        for (int offsetX = -halfSize; offsetX <= halfSize; ++offsetX) {
            QPoint currentposition = position + QPoint(offsetX, offsetY);

            if (image.rect().contains(currentposition)) {
                image.setPixelColor(currentposition, drawColor);
            }
        }
    }
}

void Tools::applyEraser(QImage &image, const QPoint &position) {
    int halfSize = m_eraserSize / 2;
    QColor eraserColor = QColor(Qt::white);

    for (int offsetY = -halfSize; offsetY <= halfSize; ++offsetY) {

        for (int offsetX = -halfSize; offsetX <= halfSize; ++offsetX) {
            QPoint currentposition = position + QPoint(offsetX, offsetY);

            if (image.rect().contains(currentposition)) {
                image.setPixelColor(currentposition, eraserColor);
            }
        }
    }
}

void Tools::applyFill(QImage &image, const QPoint &position) {
    QColor targetColor = image.pixelColor(position);
    QColor fillColor = toQColor(m_currentColor);

    if (targetColor == fillColor) {
        return;
    }

    QStack<QPoint> pointStack;
    pointStack.push(position);

    while (!pointStack.isEmpty()) {
        QPoint currentPoint = pointStack.pop();

        if (!image.rect().contains(currentPoint)) {
            continue;
        }
        if (image.pixelColor(currentPoint) != targetColor) {
            continue;
        }

        image.setPixelColor(currentPoint, fillColor);
        pointStack.push(QPoint(currentPoint.x() + 1, currentPoint.y()));
        pointStack.push(QPoint(currentPoint.x() - 1, currentPoint.y()));
        pointStack.push(QPoint(currentPoint.x(), currentPoint.y() + 1));
        pointStack.push(QPoint(currentPoint.x(), currentPoint.y() - 1));
    }
}

void Tools::setPenSize(int size) {
    if (size < 1) {
        size = 1;
    } else if (size > 9) {
        size = 9;
    }

    m_penSize = size;
}

int Tools::penSize() const {
    return m_penSize;
}

void Tools::setEraserSize(int size) {
    if (size < 1) {
        size = 1;
    } else if (size > 9) {
        size = 9;
    }

    m_eraserSize = size;
}

int Tools::eraserSize() const {
    return m_eraserSize;
}
