#ifndef REDOUNDO_H
#define REDOUNDO_H

/**
 * @file RedoUndo.h
 * @brief Header file for the undo/redo command functionality in the sprite editor
 * @details Implements QUndoCommand to handle pixel color changes with undo/redo capability
 * @author Arthur Mo (main)
 *
 * Checked by Jason Chang, Kirra Kotsenburg
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
     * @param positions Vector of pixel positions affected
     * @param oldColors Vector of original colors before change
     * @param newColor The new color being applied
     * @param frameIndex Index of the frame being modified
     */
    RedoUndoCommand(SpriteEditorModel* model, const QVector<QPoint>& positions,
                    const QVector<QColor>& oldColors, const QColor& newColor,
                    int frameIndex);

    /**
     * @brief Reverts the changes made by this command
     * @details Restores the original colors to the modified pixels
     */
    void undo() override;

    /**
     * @brief Applies or reapplies the changes made by this command
     * @details Sets the new color to all affected pixels
     */
    void redo() override;

private:
    SpriteEditorModel* m_model;
    QVector<QPoint> m_positions;    // Positions of affected pixels
    QVector<QColor> m_oldColors;    // Original colors before change
    QColor m_newColor;              // New color being applied
    int m_frameIndex;
};

#endif // REDOUNDO_H
