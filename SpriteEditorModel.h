#ifndef SPRITEEDITORMODEL_H
#define SPRITEEDITORMODEL_H

#include <QObject>
#include <QImage>
#include <QVector>
#include <QColor>
#include <QJsonObject>
#include "tools.h"

class SpriteEditorModel : public QObject {
    Q_OBJECT
public:
    explicit SpriteEditorModel(QObject *parent = nullptr);

    // create a new project
    void createNewProject(int width, int height);

    // add new frame
    void addFrame();

    // remove the current frame
    void removeFrame();
    // handle move up
    void moveFrameUp(int index);
    // handle move down
    void moveFrameDown(int index);

    // get the selected frame by index
    QImage getFrame(int index) const;

    //get the framesList size
    int getFramesListSize();

    // update the pixel color with the provided position
    void setPixel(int x, int y);

    void loadSprite(const QString& fileName);

    void saveSprite(const QString& fileName);

    // return current Canvas size (for new frame usage)
    QSize getFrameSize() const;

    void setFrameSize(int size);

    // use index to change current frame
    void setCurrentFrame(int index);

    //get current frame
    QImage& getCurrentFrame();

    // slot to update the current selected color
    void setCurrentColor(const QColor &color);

    // set the tool to current tool
    void setCurrentTool(Tools::ToolType tool);

    //get the maxium size of canvas
    QSize getMaxSize() const;

    // get the Tool from model
    Tools::ToolType getCurrentTool();

    //getCurrentColor
    QColor getCurrentColor();

    //get current index
    int getCurrentIndex();

    QVector<QImage> getFrames();

    void resizeAllFrames(int newSize);




signals:
    // signal is sent to View to update the selected color
    void colorChanged(QColor color);
    void frameListChanged();

private:
    // current frame
    QVector<QImage> m_frames;
    // current color
    QColor m_currentColor = Qt::black;
    // setting size
    QSize m_frameSize;
    // defualt size
    QSize m_defualSize = QSize(32,32);

    QJsonObject frameToJson(const QImage &frame) const;
    QImage jsonToFrame(const QJsonObject &json) const;

    // current tool
    Tools::ToolType m_currentTool;

    //current frame
    int m_currentFrameIndex;

    // Canvas size
    int maxSize;

};

#endif // SPRITEEDITORMODEL_H
