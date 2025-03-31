#ifndef SPRITEEDITORMODEL_H
#define SPRITEEDITORMODEL_H

/**
 * @file SpriteEditorModel.h
 * @brief Header file for the sprite editor model
 * @details Contains the core data and business logic for the sprite editor
 * @author Arthur Mo (main), Kirra Kostenburg (save/load), Jay Lee (Animation)
 */

#include <QObject>
#include <QImage>
#include <QVector>
#include <QColor>
#include <QJsonObject>
#include "tools.h"
#include <QUndoStack>

/**
 * @class SpriteEditorModel
 * @brief Model class for the sprite editor application
 * @details Manages the sprite data, frame storage, and editing operations
 */
class SpriteEditorModel : public QObject {
    Q_OBJECT


public:
    explicit SpriteEditorModel(QObject* parent = nullptr);

    // Project Management
    /**
     * @brief Creates a new sprite project with specified dimensions
     * @param width Width of the sprite canvas
     * @param height Height of the sprite canvas
     */
    void createNewProject(int width, int height);

    /**
     * @brief Adds a new transparent frame to the sprite
     * @details Creates both a new QImage frame and associated QUndoStack
     */
    void addFrame();

    /**
     * @brief Removes the current frame from the sprite
     * @details Maintains at least one frame. Updates current frame index if needed.
     */
    void removeFrame();

    // Frame Navigation
    /**
     * @brief Moves frame focus up in the sequence
     * @param index Current frame index
     */
    void moveFrameUp(int index);

    /**
     * @brief Moves frame focus down in the sequence
     * @param index Current frame index
     */
    void moveFrameDown(int index);

    // Frame Access
    /**
     * @brief Gets a reference to a specific frame
     * @param index Frame index to retrieve
     * @return Reference to the requested QImage frame
     */
    QImage& getFrame(int index);

    /**
     * @brief Gets the number of frames in the sprite
     * @return Current frame count
     */
    int getFramesListSize();

    // Pixel Editing
    /**
     * @brief Sets pixel color at specified coordinates
     * @param x X coordinate (column)
     * @param y Y coordinate (row)
     */
    void setPixel(int x, int y);

    /**
     * @brief Internal method for setting pixel color with undo/redo support
     * @param pos Pixel position
     * @param color Color to set
     */
    void extracted(int &width, int &height, QJsonArray &framesArray);

    // File I/O
    /**
     * @brief Loads sprite from JSON file
     * @param fileName Path to sprite file
     */
    void loadSprite(const QString &fileName);

    /**
     * @brief Saves sprite to JSON file
     * @param fileName Destination file path
     */
    void saveSprite(const QString& fileName);

    // Getters
    /**
     * @brief Gets current canvas dimensions
     * @return Size of frames in pixels
     */
    QSize getFrameSize() const;

    /**
     * @brief Gets current Frame
     * @return current frame reference
     */
    QImage& getCurrentFrame();

    /**
     * @brief Gets maximum allowed canvas size
     * @return Maximum dimensions in pixels
     */
    QSize getMaxSize() const;

    /**
     * @brief Gets current editing tool
     * @return Active tool type
     */
    Tools::ToolType getCurrentTool();

    /**
     * @brief Gets current drawing color
     * @return Active color
     */
    QColor getCurrentColor();

    /**
     * @brief Gets current frame index
     * @return Index of active frame
     */
    int getCurrentIndex();

    /**
     * @brief Gets all frames as a vector
     * @return Copy of frame collection
     */
    QVector<QImage> getFrames();

    /**
     * @brief Sets active frame by index
     * @param index Frame to make active
     */
    void setCurrentFrame(int index);

    /**
     * @brief Gets the current undo stack
     * @return Pointer to active QUndoStack
     */
    QUndoStack* currentUndoStack() const;

    // slot to update the current selected color
    void setCurrentColor(const QColor &color);

    void setFrameSize(int size);

    // set the tool to current tool
    void setCurrentTool(Tools::ToolType tool);

    // a method only serves for Redo/Undo stack
    void setUndoPixelColor(const QPoint& pos, const QColor& color);

    void clearCurrentUndoStack();

    // set the limitation for undo stack
    void setUndoLimit(int limit);





    // resize all frames
    void resizeAllFrames(int newSize);

    //Create copy of currently selected frame
    void duplicateFrame(int index);

    //Horizontal flip
    void flipHorizontal();

    // Clear the current frame (set all pixels to transparent)
    void clearCurrentFrame();





signals:
    // signal is sent to View to update the selected color
    void colorChanged(QColor color);
    void frameListChanged();
    void undoStackChanged();
    void pixelsChanged();

private:
    // current frame
    QVector<QImage> m_frames;
    // current color
    QColor m_currentColor = Qt::black;
    // setting size
    QSize m_frameSize;
    // defualt size
    QSize m_defualSize = QSize(32,32);

    QJsonObject frameToJson(const QImage &frame) const;
    QImage jsonToFrame(const QJsonObject &json) const;

    // current tool
    Tools::ToolType m_currentTool;

    //current frame
    int m_currentFrameIndex = 0;

    // Canvas size
    int maxSize;
    // undo storage
    QList<QUndoStack*> m_frameUndoStacks;

    // undo limitations
    int m_undoLimit = 10;

};

#endif // SPRITEEDITORMODEL_H
