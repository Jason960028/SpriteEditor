#ifndef SPRITEEDITORMODEL_H
#define SPRITEEDITORMODEL_H

#include <QObject>
#include <QImage>
#include <QVector>
#include <QColor>
#include <QJsonObject>
#include "tools.h"

class spriteEditorModel : public QObject {
    Q_OBJECT
public:
    explicit spriteEditorModel(QObject *parent = nullptr);

    // create a new project
    void createNewProject(int width, int height);
    // add new frame
    void addFrame();
    // remove the current frame
    void removeFrame(int index);
    // get the selected frame index
    QImage getFrame(int index) const;
    // frame number for preview fps
    int frameCount() const;

    // update the pixel color with the provided position
    void setPixel(int x, int y);

    // save the current project to be Json file
    bool saveProject(const QString &filename);
    // load the project from Json file
    bool loadProject(const QString &filename);

    // current selected color
    QColor currentColor() const;

    // return current Canvas size (for new frame usage)
    QSize frameSize() const;

    void setCurrentFrame(int index);
    // slot to update the current selected color
    void setCurrentColor(const QColor &color);



signals:
    // signal is sent to View to switch to selected frame
    void frameChanged();
    // signal is sent to View to update the FrameList
    void framesUpdated();
    // signal is sent to View to update the selected color
    void colorChanged(QColor color);

private:
    // current frame
    QVector<QImage> m_frames;
    // current color
    QColor m_currentColor = Qt::black;
    // setting size
    QSize m_frameSize = QSize(32, 32);
    // defualt size
    QSize m_defualSize = QSize(32,32);

    QJsonObject frameToJson(const QImage &frame) const;
    QImage jsonToFrame(const QJsonObject &json) const;

    // current tool
    Tools *currentTool;

    //current frame
    QImage currentFrame;
};

#endif // SPRITEEDITORMODEL_H
