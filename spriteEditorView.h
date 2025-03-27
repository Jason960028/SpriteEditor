#ifndef SPRITEEDITORVIEW_H
#define SPRITEEDITORVIEW_H

#include <QMainWindow>
#include "spriteEditorModel.h"
#include "spriteEditorController.h"
#include "canvas.h"
#include "tools.h"

class QToolButton;

namespace Ui {
class spriteEditorView;
}

class spriteEditorView : public QMainWindow
{
    Q_OBJECT

public:
    explicit spriteEditorView(spriteEditorModel* model,
                              spriteEditorController* controller,
                              QWidget* parent = nullptr);
    ~spriteEditorView();

private slots:
    // handle the addFrame button and call model to update
    void onAddFrameClicked();
    // handle the deleteFrame button and call model to update
    void onRemoveFrameClicked();
    // handle playButton and call preview to play
    void onPlayClicked();
    // handle stopButton and call preview to stop
    void onStopClicked();

private:
    void setupUI();
    void setupTools();
    void connectSignals();

    Ui::spriteEditorView* ui;

    spriteEditorModel* m_model;
    spriteEditorController* m_controller;
    canvas* m_canvasWidget;

    // Tools
    Tools* m_penTool;
    Tools* m_eraserTool;
    Tools* m_activeTool;

    // UI Elements
    QToolButton* m_penButton;
    QToolButton* m_eraserButton;
    QToolButton* m_addFrameButton;
    QToolButton* m_removeFrameButton;
    QToolButton* m_playButton;
    QToolButton* m_stopButton;
};

#endif // SPRITEEDITORVIEW_H
