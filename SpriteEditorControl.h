#ifndef SPRITEEDITORCONTROL_H
#define SPRITEEDITORCONTROL_H

#include <QObject>
#include "Tools.h"

class SpriteEditorModel;

class SpriteEditorController : public QObject
{
    Q_OBJECT
public:
    explicit SpriteEditorController(SpriteEditorModel* model, QObject* parent = nullptr);

public slots:
    void addFrame();
    void removeCurrentFrame();
    void handlePlayPressed();
    void handleStopPressed();
    void handleFrameSelected(int index);
    void moveFrameUp(int index);
    void moveFrameDown(int index);
    void onPenClicked();
    void onEraserClicked();
    void onFillClicked();

signals:
    void animationStateChanged(bool playing);
    void frameListChanged(int currentIndex);

private:
    SpriteEditorModel* m_model;
    Tools::ToolType m_currentTool;
};

#endif // SPRITEEDITORCONTROL_H
