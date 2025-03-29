#include "spriteeditormodel.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QPainter>

SpriteEditorModel::SpriteEditorModel(QObject *parent)
    : QObject(parent),
    m_currentColor(Qt::black),
    m_frameSize(32, 32),
    m_currentTool(Tools::ToolType::Pen),
    maxSize(64)
{
    // Initialize with one blank frame
    m_frames.append(QImage(m_frameSize, QImage::Format_ARGB32));
    m_frames.last().fill(Qt::transparent);
    m_currentFrameIndex = 0;
}

void SpriteEditorModel::createNewProject(int width, int height) {
    m_frames.clear();
    m_frameSize = QSize(width, height);
    addFrame();
}

void SpriteEditorModel::addFrame() {
    m_frames.append(QImage(m_frameSize, QImage::Format_ARGB32));
    m_frames.last().fill(Qt::transparent);
}

void SpriteEditorModel::removeFrame(){
    int IndexToRemove = getCurrentIndex();

    // checking if the frame is first one
    if(IndexToRemove >0){
        setCurrentFrame(IndexToRemove-1);
    }
    m_frames.remove(IndexToRemove);
}

QImage SpriteEditorModel::getFrame(int index) const {
    return index < m_frames.size() ? m_frames[index] : QImage();
}

int SpriteEditorModel::getFramesListSize(){
    return m_frames.size();
}

void SpriteEditorModel::setPixel(int x, int y) {
    QImage& currentFrame = getCurrentFrame();
    if(x >= 0 && y >= 0 && x < m_frameSize.width() && y < m_frameSize.height()) {
        currentFrame.setPixelColor(x, y, m_currentColor);

    }
}

void SpriteEditorModel::setCurrentTool(Tools::ToolType tool){
    m_currentTool = tool;
}

Tools::ToolType SpriteEditorModel::getCurrentTool(){
    return m_currentTool;
}

int SpriteEditorModel::getCurrentIndex(){
    return m_currentFrameIndex;
}

QColor SpriteEditorModel::getCurrentColor(){
    return m_currentColor;
}

QSize SpriteEditorModel::getFrameSize() const{
    return m_frameSize;
}

void SpriteEditorModel::setFrameSize(int size){
    m_frameSize = QSize(size, size);
}

QSize SpriteEditorModel::getMaxSize () const{
    return QSize(maxSize, maxSize);
}

// In spriteEditorModel.cpp
void SpriteEditorModel::setCurrentFrame(int index) {
    if(index >= 0 && index < m_frames.size()) {
        m_currentFrameIndex = index;
    }
}

QImage& SpriteEditorModel::getCurrentFrame(){
    return m_frames[m_currentFrameIndex];
}

void SpriteEditorModel::moveFrameUp(int index) {
    if (index > 0 && index < m_frames.size()) {
        m_currentFrameIndex = index - 1;
    }
}

void SpriteEditorModel::moveFrameDown(int index) {
    if (index >= 0 && index < m_frames.size() - 1) {
        m_currentFrameIndex = index + 1;
    }
}

void SpriteEditorModel::resizeAllFrames(int newSize) {
    if (newSize < 8 || newSize > maxSize) {
        return;
    }

    QSize newFrameSize(newSize, newSize);
    for (QImage& oldFrame : m_frames) {
        QImage newFrame(newFrameSize, QImage::Format_ARGB32);
        newFrame.fill(Qt::transparent);

        QPainter painter(&newFrame);
        painter.drawImage(0, 0, oldFrame);
        painter.end();

        oldFrame = newFrame;
    }

    m_frameSize = newFrameSize;
}
