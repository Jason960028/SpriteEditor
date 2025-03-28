#include "SpriteEditorModel.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>

SpriteEditorModel::SpriteEditorModel(QObject *parent)
    : QObject(parent),
    m_currentColor(Qt::black),
    m_currentTool(Tools::ToolType::Pen),
    maxGridWidth(128),
    maxGridHeight(128),
    m_frameSize(32, 32)  // Initialize frameSize FIRST
{
    // Initialize with one blank frame
    m_frames.append(QImage(m_frameSize, QImage::Format_ARGB32));
    m_frames.last().fill(Qt::transparent);
    m_currentFrame = m_frames.first();  // Now safe to access

    // In Model constructor:
    qDebug() << "Model created - frame size:" << m_frameSize
             << "frames:" << m_frames.size();
}

void SpriteEditorModel::createNewProject(int width, int height) {
    m_frames.clear();
    m_frameSize = QSize(width, height);
    addFrame();
}

void SpriteEditorModel::addFrame() {
    m_frames.append(QImage(m_frameSize, QImage::Format_ARGB32));
    m_frames.last().fill(Qt::transparent);

    // Set the new frame as current
    m_currentFrame = m_frames.last();

    // Notify UI to update the frame list and current frame
    emit framesUpdated();
    emit frameChanged();
}

void SpriteEditorModel::removeFrame() {
    if (m_frames.size() <= 1) {
        return; // Don't remove the last frame
    }

    int indexToRemove = getCurrentIndex();

    // Select a different frame before removing the current one
    if (indexToRemove > 0) {
        setCurrentFrame(indexToRemove - 1);
    } else {
        setCurrentFrame(0); // Stay on first frame if removing the first
    }

    // Now remove the frame
    m_frames.remove(indexToRemove);

    // Notify UI to update the frame list
    emit framesUpdated();
}

QImage SpriteEditorModel::getFrame(int index) const {
    return index < m_frames.size() ? m_frames[index] : QImage();
}

int SpriteEditorModel::getFramesListSize() {
    return m_frames.size();
}

void SpriteEditorModel::setPixel(int x, int y) {
    if (x >= 0 && y >= 0 && x < m_frameSize.width() && y < m_frameSize.height()) {
        // Find the index of the current frame
        int index = getCurrentIndex();

        // Update both the stored copy and the current frame reference
        m_frames[index].setPixelColor(x, y, m_currentColor);
        m_currentFrame.setPixelColor(x, y, m_currentColor);

        emit frameChanged();
    }
}

void SpriteEditorModel::setCurrentTool(Tools::ToolType tool) {
    m_currentTool = tool;
}

Tools::ToolType SpriteEditorModel::getCurrentTool() {
    return m_currentTool;
}

int SpriteEditorModel::getCurrentIndex() {
    return m_frames.indexOf(m_currentFrame);
}

QColor SpriteEditorModel::getCurrentColor() {
    return m_currentColor;
}

QSize SpriteEditorModel::frameSize() const {
    return m_frameSize;
}

QSize SpriteEditorModel::getMaxSize() const {
    return QSize(maxGridWidth, maxGridHeight);
}

void SpriteEditorModel::setCurrentFrame(int index) {
    if (index >= 0 && index < m_frames.size()) {
        m_currentFrame = m_frames[index];
        emit frameListChanged(); // Signal for frame selection change
        emit frameChanged();     // Signal for frame content change
    }
}

void SpriteEditorModel::moveFrameUp(int index) {
    if (index > 0 && index < m_frames.size()) {
        m_frames.swapItemsAt(index, index - 1);
        setCurrentFrame(index - 1);
        emit framesUpdated();
    }
}

void SpriteEditorModel::moveFrameDown(int index) {
    if (index >= 0 && index < m_frames.size() - 1) {
        m_frames.swapItemsAt(index, index + 1);
        setCurrentFrame(index + 1);
        emit framesUpdated();
    }
}

QImage SpriteEditorModel::getCurrentFrame() {
    if (m_currentFrame.isNull()) {
        return QImage(m_frameSize.isValid() ? m_frameSize : QSize(32, 32),
                      QImage::Format_ARGB32);
    }
    return m_currentFrame;
}

void SpriteEditorModel::setCurrentColor(const QColor &color) {
    m_currentColor = color;
    emit colorChanged(color); // tells the UI
}

bool SpriteEditorModel::saveProject(const QString &filename) {
    // Implementation needed
    return false;
}

void SpriteEditorModel::erasePixel(int x, int y)
{
    if (x >= 0 && y >= 0 && x < m_frameSize.width() && y < m_frameSize.height()) {
        // Find the index of the current frame
        int index = getCurrentIndex();

        // Set pixel to transparent in both the stored frame and current reference
        m_frames[index].setPixelColor(x, y, Qt::transparent);
        m_currentFrame.setPixelColor(x, y, Qt::transparent);

        emit frameChanged();
    }
}

void SpriteEditorModel::fillArea(int x, int y)
{
    if (x >= 0 && y >= 0 && x < m_frameSize.width() && y < m_frameSize.height()) {
        // Find the index of the current frame
        int index = getCurrentIndex();

        // Use the Tools fill algorithm on the stored frame
        Tools::fillArea(m_frames[index], QPoint(x, y), m_currentColor);

        // Update the current frame reference to match
        m_currentFrame = m_frames[index];

        emit frameChanged();
    }
}
