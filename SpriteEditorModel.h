#ifndef SPRITEEDITORMODEL_H
#define SPRITEEDITORMODEL_H
#include <Qstring>
#include <QImage>
#include <vector>

class spriteEditorModel
{
public:
    spriteEditorModel();

    // Add methods for model logic here, e.g., loading and saving sprites.
    void loadSprite(const QString& fileName);
    void saveSprite(const QString& fileName);
    void addFrames(QImage& image);
    void updateFrame(const QImage& updatedImage);
    std::vector<QImage> getFrames();

    void undo();
    void redo();

private:
    std::vector<QImage> m_frames;

    // Stack to hold the history of frames for undo/redo
    std::vector<std::vector<QImage>> m_undoStack;
    std::vector<std::vector<QImage>> m_redoStack;

    // Helper methods to save the current state to undo/redo stacks
    void saveStateToUndoStack();
    void clearRedoStack();
};

#endif // SPRITEEDITORMODEL_H

