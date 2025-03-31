#ifndef SPRITEEDITORCONTROLLER_H
#define SPRITEEDITORCONTROLLER_H

/**
 * @file SpriteEditorController.h
 * @brief Header file for the sprite editor controller
 * @details Handles user input and coordinates between model and view components
 * @author Arthur (main)
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
class SpriteEditorController : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor for the sprite editor controller
     * @param model Pointer to the sprite editor model
     * @param parent Parent QObject
     */
    explicit SpriteEditorController(SpriteEditorModel* model, QObject* parent = nullptr);


    // Animation control methods

    // Starts the animation playback
    void playAnimation();

    // Stops the animation playback
    void stopAnimation();

    // Sets the view component
    void setView(SpriteEditorView* view);

signals:
    // signal to change frame list
    void frameListChanged(int size);

    // signal to play or stop animation
    void animationStateChanged(bool playing);

    void toolSelectSignal(Tools::ToolType& tool);

    void currentFrameChanged();

public slots:
    // slot to handle Play button
    void handlePlayPressed();

    // slot to handle stop button
    void handleStopPressed();

    // slot to update current tool to Pen
    void onPenClicked();

    // slot to update current tool to Eraser
    void onEraserClicked();

    //slot to update current tool to Filling
    void onFillingClicked();

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

    // slot to handle load clicked
    void onLoadClicked();

    // slot to handle save clicked
    void onSaveClicked();

    // slot to handle color selection
    void onColorSelected(const QColor& color);

    // slot to handle filp clicked
    void onFlipHorizontalClicked();

    // slot to handle clean clicked
    void onCleanButtonClicked();




private:

    // Updates the state of tool buttons in the UI
    void updateToolButtonStates();

    // Pointer to the model component
    SpriteEditorModel* m_model;

    // Currently selected tool
    Tools::ToolType m_currentTool;

    // Parent widget
    QWidget* m_parentWidget;

    // Pointer to the view component
    SpriteEditorView* m_view = nullptr;
};

#endif // SPRITEEDITORCONTROLLER_H
