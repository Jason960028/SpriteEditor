#ifndef SPRITECONTROL_H
#define SPRITECONTROL_H

#include <QObject>

class spriteEditorModel;
class spriteEditorView;

class SpriteController : public QObject
{
    Q_OBJECT
public:
    explicit SpriteController(spriteEditorModel *model, spriteEditorView *view, QObject *parent = nullptr);

private slots:
    void handleToolChange(int tool);
    void handleColorChange(QColor color);
    void handleAddFrame();
    void handleRemoveFrame();
    void handlePlayAnimation();
    void handleFpsChange(int fps);

private:
    spriteEditorModel *m_model;
    spriteEditorView *m_view;
};

#endif
