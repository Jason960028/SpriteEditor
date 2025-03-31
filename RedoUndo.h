#ifndef REDOUNDO_H
#define REDOUNDO_H

/**
 * @file RedoUndo.h
 * @brief Header file for the undo/redo command functionality in the sprite editor
 * @details Implements QUndoCommand to handle pixel color changes with undo/redo capability
 * @author Arthur (main)
 */

#include <QUndoCommand>
#include <QColor>
#include <QPoint>

class SpriteEditorModel;

/**
 * @class RedoUndoCommand
 * @brief Command class for handling pixel color changes with undo/redo functionality
 * @details Stores the state of pixel changes to allow reverting and reapplying modifications
 */
class RedoUndoCommand : public QUndoCommand {

public:
    /**
     * @brief Constructor for the undo/redo command
     * @param model Pointer to the sprite editor model
     * @param positions of pixel positions affected
     * @param oldColors of original colors before change
     * @param newColor The new color being applied
     * @param frameIndex Index of the frame being modified
     */
    RedoUndoCommand(SpriteEditorModel* model, const QVector<QPoint>& positions, const QVector<QColor>& oldColors, const QColor& newColor, int frameIndex);

    //Reverts the changes made by this command
    void undo() override;
    //Applies or reapplies the changes made by this command
    void redo() override;

private:
    // Pointer to the sprite editor model
    SpriteEditorModel* m_model;
    // Positions of affected pixels
    QVector<QPoint> m_positions;
    // Original colors before change
    QVector<QColor> m_oldColors;
    // New color being applied
    QColor m_newColor;
    // Index of the frame being modified
    int m_frameIndex;
};

#endif // REDOUNDO_H
