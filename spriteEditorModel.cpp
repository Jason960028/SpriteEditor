#include "spriteeditormodel.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>

spriteEditorModel::spriteEditorModel(QObject *parent)
    : QObject(parent), m_currentColor(Qt::black), m_currentTool(Tools::currentTool()){
    //initialize the first frame
    m_frames.append(QImage(m_defualSize, QImage::Format_ARGB32));
    m_frames.last().fill(Qt::transparent);
    m_currentFrame = m_frames.first();
}

void spriteEditorModel::createNewProject(int width, int height) {
    m_frames.clear();
    m_frameSize = QSize(width, height);
    addFrame();
}

void spriteEditorModel::addFrame() {
    m_frames.append(QImage(m_frameSize, QImage::Format_ARGB32));
    m_frames.last().fill(Qt::transparent);
    emit framesUpdated(); // tells UI to update the frame list
}

void spriteEditorModel::removeFrame(){
    int IndexToRemove = getCurrentIndex();

    // checking if the frame is first one
    if(IndexToRemove >0){
        setCurrentFrame(IndexToRemove-1);
    }else{
        setCurrentFrame(IndexToRemove+1);
    }


    m_frames.remove(IndexToRemove);

    emit frameChanged();
}

QImage spriteEditorModel::getFrame(int index) const {
    return index < m_frames.size() ? m_frames[index] : QImage();
}

void spriteEditorModel::setPixel(int x, int y) {
    if(x >= 0 && y >= 0 && x < m_frameSize.width() && y < m_frameSize.height()) {
        m_currentFrame.setPixelColor(x, y, m_currentColor);

    }
}

int spriteEditorModel::getCurrentIndex(){
    return m_frames.indexOf(m_currentFrame);
}

QColor spriteEditorModel::getCurrentColor(){
    return m_currentColor;
}

QSize spriteEditorModel::frameSize() const{
    return m_frameSize;
}

void spriteEditorModel::setCurrentFrame(int index){
    m_currentFrame = m_frames[index];
    emit frameListChanged();// tells the QPainter to render the color (QPainter.drawImage(x, y, image)) render the position with the color which stored by image
}

void spriteEditorModel::setCurrentColor(const QColor &color){
    m_currentColor = color;
    emit colorChanged(color); // tells the UI
}


bool spriteEditorModel::saveProject(const QString &filename) {
    return false;
}





