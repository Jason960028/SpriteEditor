#include "spriteeditormodel.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>

spriteEditorModel::spriteEditorModel(QObject *parent)
    : QObject(parent), m_currentColor(Qt::black), currentTool(Tools::currentTool()){
    //initialize the first frame
    m_frames.append(QImage(m_defualSize, QImage::Format_ARGB32));
    m_frames.last().fill(Qt::transparent);
    currentFrame = m_frames.first();
}

void spriteEditorModel::createNewProject(int width, int height) {
    m_frames.clear();
    m_frameSize = QSize(width, height);
    addFrame();
}

void spriteEditorModel::addFrame() {
    m_frames.append(QImage(m_frameSize, QImage::Format_ARGB32));
    m_frames.last().fill(Qt::transparent);
    emit framesUpdated();
}

void spriteEditorModel::removeFrame(int index){
    m_frames.remove(index);

}

QImage spriteEditorModel::getFrame(int index) const {
    return index < m_frames.size() ? m_frames[index] : QImage();
}

void spriteEditorModel::setPixel(int x, int y) {
    if(x >= 0 && y >= 0 && x < m_frameSize.width() && y < m_frameSize.height()) {
        currentFrame.setPixelColor(x, y, m_currentColor);

    }
}

QSize spriteEditorModel::frameSize() const{
    return m_frameSize;
}

void spriteEditorModel::setCurrentFrame(int index){
    currentFrame = m_frames[index];
    emit frameChanged();// tells the QPainter to render the color (QPainter.drawImage(x, y, image)) render the position with the color which stored by image
}

void spriteEditorModel::setCurrentColor(const QColor &color){
    m_currentColor = color;
}


bool spriteEditorModel::saveProject(const QString &filename) {
    return false;
}





