#ifndef SPRITEEDITORVIEW_H
#define SPRITEEDITORVIEW_H

#include <QMainWindow>
#include "SpriteEditorModel.h"
#include "SpriteEditorController.h"
#include "canvas.h"
#include "tools.h"
#include "Animation.h"
#include <QListWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QPushButton>

class QToolButton;

namespace Ui {
class SpriteEditorView;
}

class SpriteEditorView : public QMainWindow
{
    Q_OBJECT

public:
    explicit SpriteEditorView(SpriteEditorModel* model,
                              SpriteEditorController* controller,
                              QWidget* parent = nullptr);
    ~SpriteEditorView();

    void updateCanvasDisplay();
    void applyResize(int size);




signals:
    void addFrameRequested();
    void deleteFrameRequested(int index);
    void moveFrameUpRequested(int index);
    void moveFrameDownRequested(int index);
    void frameSelected(int index);
    void loadClicked();
    void saveClicked();
    void colorSelected(const QColor& color);




private slots:

    void handleMousePressed(const QPoint& pos);

    void handleMouseDragged(const QPoint& pos);

    void handleMouseReleased(const QPoint& pos);
    //handle the Canvas update when frame changed
    void handleFrameChanged();

    void updateFrameList(int currentIndex);

    void onAddFrameClicked();

    void onDeleteFrameClicked();

    void onMoveUpClicked();

    void onMoveDownClicked();

    void onFrameSelectionChanged();

    void updateToolButtonStates();

    // slot to handle resize
    void onResizeClicked();



    // Slot to update the preview when Animation emits frameChanged signal
    void updatePreviewFrame(const QImage &frame);

    // Slots triggered when Play/Stop buttons are clicked
    void onPlayButtonClicked();
    void onStopButtonClicked();

    // Save and Load Slots
    void onLoadButtonClicked();
    void onSaveButtonClicked();

    void onColorSelected(int colorIndex);
    void onModelColorChanged(const QColor& color);
    void updateSelectedColorButton(int colorIndex);

private:
    void setupUI();
    void setupTools();
    void connectSignals();

    Ui::SpriteEditorView* ui;

    SpriteEditorModel* m_model;
    SpriteEditorController* m_controller;
    Canvas* m_canvasWidget;

    // Tool
    Tools::ToolType m_currentTool;

    QImage m_currentFrame;

    QColor m_currentColor;

    Canvas*  m_canvas;

    // UI Elements
    QToolButton* m_penButton;
    QToolButton* m_eraserButton;
    QToolButton* m_fillingButton;
    QToolButton* m_addFrameButton;
    QToolButton* m_deleteFrameButton;
    QToolButton* m_playButton;
    QToolButton* m_stopButton;
    QPushButton* m_loadButton;
    QPushButton* m_saveButton;
    QListWidget* m_frameList;
    QSpinBox* m_sizeSpinBox;
    QPushButton* m_resizeButton;
    QWidget* m_ui;

    // Animation object (for frame preview)
    Animation* m_animation;
    QImage m_previewImage;

    QVector<QToolButton*> m_colorButtons;
    QFrame* m_currentColorFrame;
    void setupColorPalette();
    QToolButton* createColorButton(const QColor& color, int index);


};

#endif // SPRITEEDITORVIEW_H


