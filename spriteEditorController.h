#ifndef SPRITEEDITORCONTROLLER_H
#define SPRITEEDITORCONTROLLER_H

#include <QObject>
#include "tools.h"

class SpriteEditorModel;

class SpriteEditorController : public QObject
{
    Q_OBJECT
public:
    explicit SpriteEditorController(SpriteEditorModel* model, QObject* parent = nullptr);


    // Frame operations


    // Animation control
    void playAnimation();
    void stopAnimation();

signals:
    // signal to change frame list
    void frameListChanged(int size);

    // signal to play or stop animation
    void animationStateChanged(bool playing);

public slots:
    // slot to handle Play button
    void handlePlayPressed();

    // slot to handle stop button
    void handleStopPressed();

    // slot to update current tool to Pen
    void onPenClicked();

    // slot to update current tool to Eraser
    void onEraserClicked();

    // slot to handle addFrame button and update frame list
    void addFrame();

    // slot to handle remove button and update frame list
    void removeCurrentFrame();

    // slot to update current frame by selected index
    void handleFrameSelected(int index);

    // slot to move to previous frame
    void moveFrameUp(int index);

    // slot to move to next frame
    void moveFrameDown(int index);

private:
    SpriteEditorModel* m_model;
    Tools::ToolType m_currentTool;
};

#endif // SPRITEEDITORCONTROLLER_H
