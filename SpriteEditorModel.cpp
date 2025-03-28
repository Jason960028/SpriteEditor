#include "spriteEditorModel.h"
#include <QFile>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>


spriteEditorModel::spriteEditorModel()
{
    // Initialization if necessary
    m_frames = {};

}

void spriteEditorModel::loadSprite(const QString& fileName)
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


void spriteEditorModel::saveSprite(const QString& fileName)
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



void spriteEditorModel::addFrames(QImage& image){
    m_frames.push_back(image);
}


void spriteEditorModel::updateFrame(const QImage& updatedImage)
{
    if (0 >= 0 && 0 < m_frames.size()) {
        m_frames[0] = updatedImage;  // Update the frame with the new image
    }
    else {
        qDebug() << "Invalid frame index!";
    }
}

std::vector<QImage> spriteEditorModel::getFrames(){
    return m_frames;
}

void spriteEditorModel::saveStateToUndoStack()
{
    // Save a copy of the current state of m_frames to the undo stack
    m_undoStack.push_back(m_frames);
}

void spriteEditorModel::clearRedoStack()
{
    // Clear the redo stack when a new action occurs after undo
    m_redoStack.clear();
}

void spriteEditorModel::undo()
{
    if (m_undoStack.empty()) return;  // Nothing to undo

    // Push the current state onto the redo stack before undoing
    m_redoStack.push_back(m_frames);

    // Pop the last state from the undo stack and set it as the current state
    m_frames = m_undoStack.back();
    m_undoStack.pop_back();
}

void spriteEditorModel::redo()
{
    if (m_redoStack.empty()) return;  // Nothing to redo

    // Push the current state onto the undo stack before redoing
    m_undoStack.push_back(m_frames);

    // Pop the last state from the redo stack and set it as the current state
    m_frames = m_redoStack.back();
    m_redoStack.pop_back();
}






