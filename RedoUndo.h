#ifndef REDOUNDO_H
#define REDOUNDO_H

/**
 * @file RedoUndo.h
 * @brief
 *
 * @author Arthur(main)
 */

#include <QUndoCommand>
#include <QColor>
#include <QPoint>

class SpriteEditorModel;

class RedoUndoCommand : public QUndoCommand {
public:
    RedoUndoCommand(SpriteEditorModel* model, const QVector<QPoint>& positions, const QVector<QColor>& oldColors, const QColor& newColor, int frameIndex);

    void undo() override;
    void redo() override;

private:
    SpriteEditorModel* m_model;
    QVector<QPoint> m_positions;
    QVector<QColor> m_oldColors;
    QColor m_newColor;
    int m_frameIndex;
};

#endif // REDOUNDO_H
