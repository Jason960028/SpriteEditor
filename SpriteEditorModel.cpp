#include "spriteeditormodel.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QPainter>


SpriteEditorModel::SpriteEditorModel(QObject *parent)
    : QObject(parent),
    m_currentColor(Qt::black),
    m_currentTool(Tools::ToolType::Pen),
    m_frameSize(32, 32),
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

void SpriteEditorModel::setCurrentColor(const QColor &color){
    m_currentColor = color;
    emit colorChanged(color); // tells the UI
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


void SpriteEditorModel::loadSprite(const QString& fileName)
{
    // Implement loading logic here
    qDebug() << "Loading sprite from " << fileName;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject root = doc.object();

    int width = root["width"].toInt();
    int height = root["height"].toInt();
    QJsonArray framesArray = root["frames"].toArray();

    m_frames.clear();

    for (const QJsonValue &frameVal : framesArray) {
        QImage frame(width, height, QImage::Format_ARGB32);
        QJsonArray rows = frameVal.toArray();

        for (int y = 0; y < height; ++y) {
            QJsonArray row = rows[y].toArray();
            for (int x = 0; x < width; ++x) {
                QJsonArray pixel = row[x].toArray();
                QColor color(pixel[0].toInt(), pixel[1].toInt(), pixel[2].toInt(), pixel[3].toInt());
                frame.setPixelColor(x, y, color);
            }
        }

        m_frames.push_back(frame);
    }

    qDebug() << "Loaded" << m_frames.size() << "frames";
}


void SpriteEditorModel::saveSprite(const QString& fileName)
{
    if (m_frames.empty()) return;

    QJsonObject spriteJson;


    int width = m_frames[0].width();
    int height = m_frames[0].height();
    int frameCount = m_frames.size();

    spriteJson["width"] = width;
    spriteJson["height"] = height;
    spriteJson["frameCount"] = frameCount;

    QJsonArray framesArray;

    for (const QImage &frame : m_frames) {
        QJsonArray framePixels;

        for (int y = 0; y < height; ++y) {
            QJsonArray row;
            for (int x = 0; x < width; ++x) {
                QColor color = frame.pixelColor(x, y);
                QJsonArray pixel;
                pixel.append(color.red());
                pixel.append(color.green());
                pixel.append(color.blue());
                pixel.append(color.alpha());
                row.append(pixel);
            }
            framePixels.append(row);
        }

        framesArray.append(framePixels);
    }

    spriteJson["frames"] = framesArray;

    QJsonDocument doc(spriteJson);
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file.write(doc.toJson(QJsonDocument::Indented));
        file.close();
        qDebug() << "Saved sprite to" << fileName;
    }
}

QVector<QImage> SpriteEditorModel::getFrames(){
    return m_frames;
}

