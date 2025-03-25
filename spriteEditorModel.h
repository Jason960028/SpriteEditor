#ifndef SPRITEEDITORMODEL_H
#define SPRITEEDITORMODEL_H

#include <QObject>
#include <QList>
#include <QImage>

class ToolManager;

class spriteEditorModel : public QObject
{
    Q_OBJECT
public:
    explicit spriteEditorModel(QObject *parent = nullptr);

    // Frame operations
    void addFrame(const QImage &frame);
    void removeFrame(int index);
    void setCurrentFrame(int index);

    // Drawing operations
    void drawAt(const QPoint &pos);

    // Animation control
    void playAnimation();
    void stopAnimation();

    // Getters
    QList<QImage> frames() const;
    QImage currentFrame() const;
    int currentFrameIndex() const;
    ToolManager* toolManager() const;

signals:
    void framesChanged(const QList<QImage> &frames); // when adding/deleting frames
    void currentFrameChanged(const QImage &frame); // when click a certain frame
    void animationStateChanged(bool playing); // when click play button

private:
    QList<QImage> m_frames;
    int m_currentFrameIndex;
    ToolManager *m_toolManager;
    bool m_isPlaying;
};

#endif
