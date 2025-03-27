#ifndef SPRITEEDITORCONTROLLER_H
#define SPRITEEDITORCONTROLLER_H

#include <QObject>
#include "tools.h"

class spriteEditorModel;

class spriteEditorController : public QObject
{
    Q_OBJECT
public:
    explicit spriteEditorController(spriteEditorModel* model, QObject* parent = nullptr);

    // Tool management
    void setActiveTool(Tools::Type toolType);
    Tools* activeTool() const { return m_activeTool; }

    // Pixel operations
    void handlePixelClick(int x, int y);
    void handlePixelDrag(int x, int y);

    // Frame operations
    void addFrame();
    void removeCurrentFrame();

    // Animation control
    void playAnimation();
    void stopAnimation();

signals:
    void toolChanged(Tools::Type newTool);
    void animationStateChanged(bool playing);

public slots:
    void onPenClicked();
    void onEraserClicked();

private:
    spriteEditorModel* m_model;
    Tools* m_activeTool;
};

#endif // SPRITEEDITORCONTROLLER_H
