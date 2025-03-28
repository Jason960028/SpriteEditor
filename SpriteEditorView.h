#ifndef SPRITEEDITORVIEW_H
#define SPRITEEDITORVIEW_H

#include <QMainWindow>
#include <QToolButton>
#include <QListWidget>
#include "tools.h"

namespace Ui {
class SpriteEditorView;
}

class SpriteEditorModel;
class SpriteEditorController;
class Canvas;

class SpriteEditorView : public QMainWindow
{
    Q_OBJECT

public:
    explicit SpriteEditorView(SpriteEditorModel* model,
                              SpriteEditorController* controller,
                              QWidget* parent = nullptr);
    ~SpriteEditorView();

private slots:
    void handleFrameChanged();
    void updateFrameList();
    void updateFrameListSelection();
    void onAddFrameClicked();
    void onDeleteFrameClicked();
    void onMoveUpClicked();
    void onMoveDownClicked();
    void onFrameSelectionChanged(int row);
    void handleMousePressed(const QPoint& pos);
    void handleMouseDragged(const QPoint& pos);
    void handleMouseReleased(const QPoint& pos);

signals:
    void addFrameRequested();
    void deleteFrameRequested(int index);
    void moveFrameUpRequested(int index);
    void moveFrameDownRequested(int index);
    void frameSelected(int index);
    void updateToolButtonStates();

private:
    void setupUI();
    void setupTools();
    void connectSignals();
    void updateCanvasDisplay();

    Ui::SpriteEditorView* ui;
    SpriteEditorModel* m_model;
    SpriteEditorController* m_controller;
    Canvas* m_canvas;

    QToolButton* m_penButton;
    QToolButton* m_eraserButton;
    QToolButton* m_fillButton;
    QToolButton* m_addFrameButton;
    QToolButton* m_deleteFrameButton;

    QListWidget* m_frameList;

    Tools::ToolType m_currentTool;
    QImage m_currentFrame;
    QColor m_currentColor;
};

#endif // SPRITEEDITORVIEW_H
