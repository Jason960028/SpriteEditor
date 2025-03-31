#ifndef SPRITEEDITORMODEL_H
#define SPRITEEDITORMODEL_H

/**
 * @file SpriteEditorModel.h
 * @brief Header file for the sprite editor model
 * @details Contains the core data and logic for the sprite editor
 * @author Arthur Mo (main), Kirra Kostenburg (save/load), Jay Lee (Animation)
 *
 * Checked by Jason Chang, Kirra Kotsenburg
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
    /**
     * @brief Constructor for the sprite editor model
     * @param parent Parent QObject
     */
    explicit SpriteEditorModel(QObject* parent = nullptr);

    // -------------Project Management-------------
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

    // -------------Frame Navigation-------------
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

    // -------------Frame Access-------------
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

    // -------------Pixel Editing-------------
    /**
     * @brief Sets pixel color at specified coordinates
     * @param x X coordinate (column)
     * @param y Y coordinate (row)
     */
    void setPixel(int x, int y);

    /**
     * @brief Method for setting pixel color with undo/redo support
     * @param pos Pixel position
     * @param color Color to set
     */
    void setUndoPixelColor(const QPoint& pos, const QColor& color);

    /**
     * @brief Method for clearing current undo stack
     */
    void clearCurrentUndoStack();

    // -------------File I/O-------------
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

    // -------------Getters-------------
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
     * @brief Gets the current undo stack
     * @return Pointer to active QUndoStack
     */
    QUndoStack* currentUndoStack() const;

    // -------------Setters-------------
    /**
     * @brief Sets active frame by index
     * @param index Frame to make active
     */
    void setCurrentFrame(int index);

    /**
     * @brief Updates the current selected color
     * @param color New color to set
     */
    void setCurrentColor(const QColor &color);

    /**
     * @brief Sets the frame size
     * @param size New size value
     */
    void setFrameSize(int size);

    /**
     * @brief Sets the current tool
     * @param tool Tool type to set
     */
    void setCurrentTool(Tools::ToolType tool);

    /**
     * @brief Sets the undo limit
     * @param limit Maximum number of undo operations
     */
    void setUndoLimit(int limit);

    // -------------Additional Handlers-------------
    /**
     * @brief Resizes all frames to a new size
     * @param newSize New size in pixels
     */
    void resizeAllFrames(int newSize);

    /**
     * @brief Creates a copy of the currently selected frame
     * @param index Frame index to duplicate
     */
    void duplicateFrame(int index);

    /**
     * @brief Flips the current frame horizontally
     */
    void flipHorizontal();

    /**
     * @brief Clears the current frame (all pixels transparent)
     */
    void clearCurrentFrame();

signals:
    /**
     * @brief Signal sent when the color changes
     * @param color New color value
     */
    void colorChanged(QColor color);

    /**
     * @brief Signal sent when the frame list changes
     */
    void frameListChanged();

    /**
     * @brief Signal sent when the undo stack changes
     */
    void undoStackChanged();

    /**
     * @brief Signal sent when pixels change
     */
    void pixelsChanged();

private:
    QVector<QImage> m_frames;              // Collection of frames
    QColor m_currentColor = Qt::black;     // Current drawing color
    QSize m_frameSize;                     // Current frame dimensions
    QSize m_defaultSize = QSize(32, 32);   // Default frame size

    QJsonObject frameToJson(const QImage &frame) const;
    QImage jsonToFrame(const QJsonObject &json) const;

    Tools::ToolType m_currentTool;         // Current drawing tool
    int m_currentFrameIndex = 0;           // Active frame index
    int m_maxSize;                         // Maximum canvas size
    QList<QUndoStack*> m_frameUndoStacks;  // Undo stacks for each frame
    int m_undoLimit = 10;                  // Maximum undo operations
};

#endif // SPRITEEDITORMODEL_H
