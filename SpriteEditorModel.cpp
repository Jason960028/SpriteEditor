#include "SpriteEditorModel.h"
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
    // Initialize first Frame and Undo Stack
    addFrame();
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

    QUndoStack* newStack = new QUndoStack(this);
    newStack->setUndoLimit(m_undoLimit); // Apply limit to new stack
    m_frameUndoStacks.append(newStack);
}

void SpriteEditorModel::removeFrame(){
    if(m_frames.size() <= 1) return;

    const int index = m_currentFrameIndex;

    // Properly delete undo stack
    delete m_frameUndoStacks.takeAt(index);
    m_frames.removeAt(index);

    // Update current index before emitting signals
    if(index >= m_frames.size())
        m_currentFrameIndex = m_frames.size() - 1;

    emit undoStackChanged();
    emit frameListChanged();
}

QImage& SpriteEditorModel::getFrame(int index){
    Q_ASSERT(index >= 0 && index < m_frames.size());
    return m_frames[index];
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

void SpriteEditorModel::setUndoPixelColor(const QPoint& pos, const QColor& color){
    if(getCurrentFrame().rect().contains(pos)) {
        getCurrentFrame().setPixelColor(pos, color);
        emit pixelsChanged();
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

void SpriteEditorModel::setCurrentFrame(int index) {
    if(index >= 0 && index < m_frames.size()) {
        m_currentFrameIndex = index;
        emit undoStackChanged();
        emit frameListChanged();
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

    for (const QJsonValue &frameVal : std::as_const(framesArray)) {
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

    for (const QImage &frame : std::as_const(m_frames)) {
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

QUndoStack* SpriteEditorModel::currentUndoStack() const {
    if(m_currentFrameIndex >= 0 &&
        m_currentFrameIndex < m_frameUndoStacks.size()) {
        return m_frameUndoStacks[m_currentFrameIndex];
    }
    // Create stack if missing (safety check)
    qWarning() << "Missing undo stack for frame" << m_currentFrameIndex;
    return new QUndoStack(const_cast<SpriteEditorModel*>(this));
}

void SpriteEditorModel::setUndoLimit(int limit) {
    m_undoLimit = qBound(10, limit, 100); // Keep between 10-100 steps

    for(QUndoStack* stack : m_frameUndoStacks) {
        stack->setUndoLimit(m_undoLimit);
    }
}
