/**
 * @file RedoUndo.cpp
 * @brief Implementation of the undo/redo command functionality
 * @details Handles storing and applying pixel color changes with undo/redo operations
 * @author Arthur Mo (main)
 *
 * Checked by Jason Chang
 */

#include "RedoUndo.h"
#include "SpriteEditorModel.h"

RedoUndoCommand::RedoUndoCommand(SpriteEditorModel* model,
                                 const QVector<QPoint>& positions,
                                 const QVector<QColor>& oldColors,
                                 const QColor& newColor,
                                 int frameIndex)
    : m_model(model),
    m_positions(positions),
    m_oldColors(oldColors),
    m_newColor(newColor),
    m_frameIndex(frameIndex) {
    // Constructor body is empty
}

void RedoUndoCommand::undo() {
    for (int i = 0; i < m_positions.size(); ++i) {
        m_model->setUndoPixelColor(m_positions[i], m_oldColors[i]);
    }
}

void RedoUndoCommand::redo() {
    for (QPoint& pos : m_positions) {
        m_model->setUndoPixelColor(pos, m_newColor);
    }
}
