#ifndef SPRITEEDITORMODEL_H
#define SPRITEEDITORMODEL_H
#include <QObject>
#include <QImage>
#include <QVector>
#include <QColor>
#include <QJsonObject>
#include "Tools.h"
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

    // get the selected frame by index
    QImage getFrame(int index) const;

    //get the framesList size
    int getFramesListSize();

    // update the pixel color with the provided position
    void setPixel(int x, int y);

    // save the current project to be Json file
    bool saveProject(const QString &filename);

    // return current Canvas size (for new frame usage)
    QSize frameSize() const;

    // use index to change current frame
    void setCurrentFrame(int index);

    //get current frame
    QImage getCurrentFrame();

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

    // move frame up in list
    void moveFrameUp(int index);

    // move frame down in list
    void moveFrameDown(int index);

    void erasePixel(int x, int y);
    void fillArea(int x, int y);
signals:
    // signal is sent to View to update the selected color
    void colorChanged(QColor color);
    void frameListChanged();
    // signal when frame list content changes
    void framesUpdated();
    // signal when current frame content changes
    void frameChanged();
private:
    // current frame list
    QVector<QImage> m_frames;
    // current color
    QColor m_currentColor = Qt::black;
    // setting size
    QSize m_frameSize;
    // defualt size
    QSize m_defualSize = QSize(32,32);
    // current tool
    Tools::ToolType m_currentTool;
    //current frame
    QImage m_currentFrame;
    // Canvas size
    int maxGridWidth;
    int maxGridHeight;
};
#endif // SPRITEEDITORMODEL_H
