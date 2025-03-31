#ifndef SPRITEEDITORCONTROLLER_H
#define SPRITEEDITORCONTROLLER_H

/**
 * @file SpriteEditorController.h
 * @brief Header file for the sprite editor controller
 * @details Handles user input and coordinates between model and view components
 * @author Arthur (main), Jason Chang(Modification for additional features)
 *
 * Checked by Jay Lee
 */

#include <QObject>
#include "tools.h"
#include <QFileDialog>

class SpriteEditorModel;
class SpriteEditorView;

/**
 * @class SpriteEditorController
 * @brief Controller class for the sprite editor application
 * @details Manages user interactions and coordinates between model and view
 */
class SpriteEditorController : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Constructor for the sprite editor controller
     * @param model Pointer to the sprite editor model
     * @param parent Parent QObject
     */
    explicit SpriteEditorController(SpriteEditorModel* model, QObject* parent = nullptr);

    /**
     * @brief Starts the animation playback
     */
    void playAnimation();

    /**
     * @brief Stops the animation playback
     */
    void stopAnimation();

    /**
     * @brief Sets the view component
     * @param view Pointer to the view
     */
    void setView(SpriteEditorView* view);

signals:
    /**
     * @brief Signal to update frame list size
     * @param size New frame list size
     */
    void frameListChanged(int size);

    /**
     * @brief Signal to update animation state
     * @param playing True if playing, false if stopped
     */
    void animationStateChanged(bool playing);

    /**
     * @brief Signal to update selected tool
     * @param tool New tool type
     */
    void toolSelectSignal(Tools::ToolType& tool);

    /**
     * @brief Signal when current frame has changed
     */
    void currentFrameChanged();

public slots:
    /**
     * @brief Handles play button press
     */
    void handlePlayPressed();

    /**
     * @brief Handles stop button press
     */
    void handleStopPressed();

    /**
     * @brief Updates current tool to Pen
     */
    void onPenClicked();

    /**
     * @brief Updates current tool to Eraser
     */
    void onEraserClicked();

    /**
     * @brief Updates current tool to Fill
     */
    void onFillingClicked();

    /**
     * @brief Adds a new frame
     */
    void addFrame();

    /**
     * @brief Removes the current frame
     */
    void removeCurrentFrame();

    /**
     * @brief Updates the selected frame
     * @param index Selected frame index
     */
    void handleFrameSelected(int index);

    /**
     * @brief Moves frame up in sequence
     * @param index Current frame index
     */
    void moveFrameUp(int index);

    /**
     * @brief Moves frame down in sequence
     * @param index Current frame index
     */
    void moveFrameDown(int index);

    /**
     * @brief Handles load button click
     */
    void onLoadClicked();

    /**
     * @brief Handles save button click
     */
    void onSaveClicked();

    /**
     * @brief Handles color selection
     * @param color Selected color
     */
    void onColorSelected(const QColor& color);

    /**
     * @brief Handles horizontal flip button click
     */
    void onFlipHorizontalClicked();

    /**
     * @brief Handles clean button click
     */
    void onCleanButtonClicked();

private:
    /**
     * @brief Updates tool button states in UI
     */
    void updateToolButtonStates();

    SpriteEditorModel* m_model;       // Pointer to model component
    Tools::ToolType m_currentTool;    // Currently selected tool
    QWidget* m_parentWidget;          // Parent widget
    SpriteEditorView* m_view = nullptr; // Pointer to view component
};

#endif // SPRITEEDITORCONTROLLER_H
