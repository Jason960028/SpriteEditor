#ifndef ANIMATION_H
#define ANIMATION_H

#include <QWidget>
#include <QImage>
#include <QVector>
#include <QTimer>

class Animation : public QWidget
{
    Q_OBJECT

public:
    explicit Animation(QWidget *parent = nullptr);
    ~Animation();

    void addFrame(const QImage &frame);        // Add a single frame
    void clearFrames();                        // Remove all frames
    void showSingleFrame(const QImage &frame); // Display only one frame (preview mode)
    void play();                               // Start the animation
    void stop();                               // Stop the animation
    void setFrameDelay(int delay);             // Set delay between frames (in milliseconds)

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<QImage> m_frames;          // List of frames
    int m_currentFrameIndex;           // Current frame being displayed
    int m_frameDelay;                  // Delay between frames (ms)
    QTimer m_timer;                    // Timer for frame switching

private slots:
    void updateFrame();               // Slot triggered by timer to move to next frame
};

#endif // ANIMATION_H
