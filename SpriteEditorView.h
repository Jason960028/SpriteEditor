#ifndef SPRITEEDITORVIEW_H
#define SPRITEEDITORVIEW_H

/**
 * @file SpriteEditorView.h
 * @brief Header file for the sprite editor view
 * @details Implements the user interface for the sprite editor
 * @author Arthur (main), Jason Chang (Canvas implementations, Color panel),
 *         Kirra Kostenburg (save/load), Jay Lee (Animation, Layer)
 */

#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>
#include "Animation.h"
#include "SpriteEditorController.h"
#include "SpriteEditorModel.h"
#include "canvas.h"
#include "tools.h"

class QToolButton;

namespace Ui {
class SpriteEditorView;
}

/**
 * @class SpriteEditorView
 * @brief View class for the sprite editor application
 * @details Implements the user interface and handles visualization
 */
class SpriteEditorView : public QMainWindow
{
    Q_OBJECT

public:
    explicit SpriteEditorView(SpriteEditorModel *model,
                              SpriteEditorController *controller,
                              QWidget *parent = nullptr);
    ~SpriteEditorView();

    // method to update Canvas
    void updateCanvasDisplay();
    // method to resize Canvas
    void applyResize(int size);

signals:
    void addFrameRequested();
    void deleteFrameRequested(int index);
    void moveFrameUpRequested(int index);
    void moveFrameDownRequested(int index);
    void frameSelected(int index);
    void loadClicked();
    void saveClicked();
    void colorSelected(const QColor &color);

private slots:

    // slot to handle mouse Pressed
    void handleMousePressed(const QPoint &pos);

    // slot to handle mouse Dragged
    void handleMouseDragged(const QPoint &pos);

    // slot to handle mouse Released
    void handleMouseReleased(const QPoint &pos);

    //handle the Canvas update when frame changed
    void handleFrameChanged();

    // slot to update the FrameList
    void updateFrameList(int currentIndex);

    // slot to handle Add frame clicked
    void onAddFrameClicked();

    // slot to handle delete frame clicked
    void onDeleteFrameClicked();

    // slot to handle move frame up clicked
    void onMoveUpClicked();

    // slot to handle move frame down clicked
    void onMoveDownClicked();

    // slot to handle Frame selected
    void onFrameSelectionChanged();

    // slot to update Tool button selected
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

    // Color selections
    void onColorSelected(int colorIndex);
    void onModelColorChanged(const QColor &color);
    void updateSelectedColorButton(int colorIndex);

    // Redo/Undo connection slot
    void updateUndoRedoConnections();

private:
    // basic UI set up
    void setupUI();
    void setupTools();
    void connectSignals();
    void setupButtonIcons();
    void applyTheme();
    Ui::SpriteEditorView *ui;
    SpriteEditorModel *m_model;
    SpriteEditorController *m_controller;
    Canvas *m_canvasWidget;

    // Tool
    Tools::ToolType m_currentTool;

    QImage m_currentFrame;

    QColor m_currentColor;

    Canvas *m_canvas;

    QAction *undoAction;
    QAction *redoAction;

    // UI Elements
    QToolButton *m_penButton;
    QToolButton *m_eraserButton;
    QToolButton *m_fillingButton;
    QToolButton *m_addFrameButton;
    QToolButton *m_deleteFrameButton;
    QToolButton *m_playButton;
    QToolButton *m_stopButton;
    QToolButton *m_flipButton;
    QPushButton *m_loadButton;
    QPushButton *m_saveButton;
    QPushButton *m_cleanButton;
    QListWidget *m_frameList;
    QSpinBox *m_sizeSpinBox;
    QPushButton *m_resizeButton;
    QWidget *m_ui;
    QUndoStack *m_currentUndoStack;

    // Animation object (for frame preview)
    Animation *m_animation;
    QImage m_previewImage;

    QVector<QToolButton *> m_colorButtons;
    QFrame *m_currentColorFrame;
    void setupColorPalette();
    QToolButton *createColorButton(const QColor &color, int index);
};

#endif // SPRITEEDITORVIEW_H
