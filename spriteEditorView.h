#ifndef SPRITEEDITORVIEW_H
#define SPRITEEDITORVIEW_H

#include <QMainWindow>
#include <QColorDialog>

class QListWidget;
class QSlider;
class CanvasWidget;
class AnimationPreview;

class spriteEditorView : public QMainWindow
{
    Q_OBJECT
public:
    explicit spriteEditorView(QWidget *parent = nullptr);

    // UI Getters
    CanvasWidget* canvas() const;
    AnimationPreview* animationPreview() const;
    QColor selectedColor() const;
    int selectedTool() const;
    int fps() const;

public slots:
    void updateFrameList(const QList<QImage>& frames);
    void setCurrentFrame(const QImage& frame);
    void setPreviewEnabled(bool enabled);




private:
    void setupUi();
    void setupToolbar();

    CanvasWidget *m_canvas;
    AnimationPreview *m_animationPreview;
    QListWidget *m_frameList;
    QColorDialog *m_colorDialog;
    QSlider *m_fpsSlider;
};

#endif
