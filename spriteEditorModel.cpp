#include "spriteeditormodel.h"
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
    emit framesUpdated(); // tells UI to update the frame list
}

void SpriteEditorModel::removeFrame(){
    int IndexToRemove = getCurrentIndex();

    // checking if the frame is first one
    if(IndexToRemove >0){
        setCurrentFrame(IndexToRemove-1);
    }else{
        setCurrentFrame(IndexToRemove+1);
    }


    m_frames.remove(IndexToRemove);

    emit frameChanged(); // tells Canvas to swicth to another frame
}

QImage SpriteEditorModel::getFrame(int index) const {
    return index < m_frames.size() ? m_frames[index] : QImage();
}

int SpriteEditorModel::getFramesListSize(){
    return m_frames.size();
}

void SpriteEditorModel::setPixel(int x, int y) {
    if(x >= 0 && y >= 0 && x < m_frameSize.width() && y < m_frameSize.height()) {
        m_currentFrame.setPixelColor(x, y, m_currentColor);

    }
}

void SpriteEditorModel::setCurrentTool(Tools::ToolType tool){
    m_currentTool = tool;
}

Tools::ToolType SpriteEditorModel::getCurrentTool(){
    return m_currentTool;
}

int SpriteEditorModel::getCurrentIndex(){
    return m_frames.indexOf(m_currentFrame);
}

QColor SpriteEditorModel::getCurrentColor(){
    return m_currentColor;
}

QSize SpriteEditorModel::frameSize() const{
    return m_frameSize;
}

QSize SpriteEditorModel::getMaxSize () const{
    return QSize(maxGridWidth, maxGridHeight);
}

// In spriteEditorModel.cpp
void SpriteEditorModel::setCurrentFrame(int index) {
    if(index >= 0 && index < m_frames.size()) {
        m_currentFrame = m_frames[index];
        emit frameListChanged();
    }
}

QImage SpriteEditorModel::getCurrentFrame(){
    if (m_currentFrame.isNull()) {
        return QImage(m_frameSize.isValid() ? m_frameSize : QSize(32, 32),
                      QImage::Format_ARGB32);
    }
    return m_currentFrame;
}

void SpriteEditorModel::setCurrentColor(const QColor &color){
    m_currentColor = color;
    emit colorChanged(color); // tells the UI
}


bool SpriteEditorModel::saveProject(const QString &filename) {
    return false;
}





