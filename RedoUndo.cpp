#include "RedoUndo.h"

#include "SpriteEditorModel.h"

RedoUndoCommand::RedoUndoCommand(SpriteEditorModel* model,
                                 const QVector<QPoint>& positions,
                                 const QVector<QColor>& oldColors,
                                 const QColor& newColor,
                                 int frameIndex)  // Initialize frame index
    : m_model(model), m_positions(positions),
    m_oldColors(oldColors), m_newColor(newColor),
    m_frameIndex(frameIndex){}

void RedoUndoCommand::undo() {
    QImage& frame = m_model->getFrame(m_frameIndex);  // Use stored index
    for (int i = 0; i < m_positions.size(); ++i) {
        frame.setPixelColor(m_positions[i], m_oldColors[i]);
    }
    m_model->emit pixelsChanged();
}

void RedoUndoCommand::redo() {
    QImage& frame = m_model->getFrame(m_frameIndex);  // Use stored index
    for (QPoint& pos : m_positions) {
        frame.setPixelColor(pos, m_newColor);
    }
    m_model->emit pixelsChanged();
}
