#ifndef SPRITEEDITORVIEW_H
#define SPRITEEDITORVIEW_H

/**
 * @file SpriteEditorView.h
 * @brief Header file for the sprite editor view
 * @details Implements the user interface for the sprite editor
 * @author Arthur (main), Jason Chang (Canvas implementations, Color panel),
 *         Kirra Kostenburg (save/load), Jay Lee (Animation, Layer)
 *
 * Checked by Jason Chang, Arthur Mo, Kirra Kostenburg, Jay Lee
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
class SpriteEditorView : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Constructor for the sprite editor view
     * @param model Pointer to the sprite editor model
     * @param controller Pointer to the sprite editor controller
     * @param parent Parent widget
     */
    explicit SpriteEditorView(SpriteEditorModel *model,
                              SpriteEditorController *controller,
                              QWidget *parent = nullptr);

    /**
     * @brief Destructor for the sprite editor view
     */
    ~SpriteEditorView();

    /**
     * @brief Updates the canvas display with current frame data
     */
    void updateCanvasDisplay();

    /**
     * @brief Applies resize operation to the canvas
     * @param size New size for the canvas
     */
    void applyResize(int size);

signals:
    /**
     * @brief Signal to request adding a new frame
     */
    void addFrameRequested();

    /**
     * @brief Signal to request deleting a frame
     * @param index Index of frame to delete
     */
    void deleteFrameRequested(int index);

    /**
     * @brief Signal to request moving a frame up
     * @param index Current frame index
     */
    void moveFrameUpRequested(int index);

    /**
     * @brief Signal to request moving a frame down
     * @param index Current frame index
     */
    void moveFrameDownRequested(int index);

    /**
     * @brief Signal when a frame is selected
     * @param index Selected frame index
     */
    void frameSelected(int index);

    /**
     * @brief Signal when load is clicked
     */
    void loadClicked();

    /**
     * @brief Signal when save is clicked
     */
    void saveClicked();

    /**
     * @brief Signal when a color is selected
     * @param color Selected color
     */
    void colorSelected(const QColor &color);

private slots:
    /**
     * @brief Handles mouse press events on canvas
     * @param pos Mouse position
     */
    void handleMousePressed(const QPoint &pos);

    /**
     * @brief Handles mouse drag events on canvas
     * @param pos Mouse position
     */
    void handleMouseDragged(const QPoint &pos);

    /**
     * @brief Handles mouse release events on canvas
     * @param pos Mouse position
     */
    void handleMouseReleased(const QPoint &pos);

    /**
     * @brief Updates UI when frame changes
     */
    void handleFrameChanged();

    /**
     * @brief Updates the frame list display
     * @param currentIndex Current frame index
     */
    void updateFrameList(int currentIndex);

    /**
     * @brief Handles add frame button click
     */
    void onAddFrameClicked();

    /**
     * @brief Handles delete frame button click
     */
    void onDeleteFrameClicked();

    /**
     * @brief Handles move frame up button click
     */
    void onMoveUpClicked();

    /**
     * @brief Handles move frame down button click
     */
    void onMoveDownClicked();

    /**
     * @brief Handles frame selection change
     */
    void onFrameSelectionChanged();

    /**
     * @brief Updates tool button states
     */
    void updateToolButtonStates();

    /**
     * @brief Handles resize button click
     */
    void onResizeClicked();

    /**
     * @brief Updates preview frame
     * @param frame Frame to update
     */
    void updatePreviewFrame(const QImage &frame);

    /**
     * @brief Handles play button click
     */
    void onPlayButtonClicked();

    /**
     * @brief Handles stop button click
     */
    void onStopButtonClicked();

    /**
     * @brief Handles load button click
     */
    void onLoadButtonClicked();

    /**
     * @brief Handles save button click
     */
    void onSaveButtonClicked();

    /**
     * @brief Handles color selection
     * @param colorIndex Index of selected color
     */
    void onColorSelected(int colorIndex);

    /**
     * @brief Updates UI when model color changes
     * @param color New color
     */
    void onModelColorChanged(const QColor &color);

    /**
     * @brief Updates the selected color button
     * @param colorIndex Index of selected color
     */
    void updateSelectedColorButton(int colorIndex);

    /**
     * @brief Updates undo/redo connections
     */
    void updateUndoRedoConnections();

private:
    /**
     * @brief Sets up the UI components
     */
    void setupUI();

    /**
     * @brief Sets up the tools
     */
    void setupTools();

    /**
     * @brief Connects signals and slots
     */
    void connectSignals();

    /**
     * @brief Sets up button icons
     */
    void setupButtonIcons();

    /**
     * @brief Applies the UI theme
     */
    void applyTheme();

    /**
     * @brief Sets up the color palette
     */
    void setupColorPalette();

    Ui::SpriteEditorView *ui;                 // UI form
    SpriteEditorModel *m_model;               // Model pointer
    SpriteEditorController *m_controller;     // Controller pointer
    Canvas *m_canvasWidget;                   // Canvas widget

    Tools::ToolType m_currentTool;            // Current tool

    QImage m_currentFrame;                    // Current frame
    QColor m_currentColor;                    // Current color
    Canvas *m_canvas;                         // Canvas

    QAction *undoAction;                      // Undo action
    QAction *redoAction;                      // Redo action

    // UI Elements
    QToolButton *m_penButton;                 // Pen tool button
    QToolButton *m_eraserButton;              // Eraser tool button
    QToolButton *m_fillingButton;             // Fill tool button
    QToolButton *m_addFrameButton;            // Add frame button
    QToolButton *m_deleteFrameButton;         // Delete frame button
    QToolButton *m_playButton;                // Play button
    QToolButton *m_stopButton;                // Stop button
    QToolButton *m_flipButton;                // Flip button
    QPushButton *m_loadButton;                // Load button
    QPushButton *m_saveButton;                // Save button
    QPushButton *m_cleanButton;               // Clean button
    QListWidget *m_frameList;                 // Frame list widget
    QSpinBox *m_sizeSpinBox;                  // Size spin box
    QPushButton *m_resizeButton;              // Resize button
    QWidget *m_ui;                            // UI widget
    QUndoStack *m_currentUndoStack;           // Current undo stack

    Animation *m_animation;                   // Animation preview
    QImage m_previewImage;                    // Preview image

    QVector<QToolButton *> m_colorButtons;    // Color buttons
    QFrame *m_currentColorFrame;              // Current color frame
};

#endif // SPRITEEDITORVIEW_H
