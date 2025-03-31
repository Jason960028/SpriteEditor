#ifndef ANIMATION_H
#define ANIMATION_H

/**
 * @file Animation.h
 * @brief Header file for the Animation class that handles sprite animation playback
 * @details Manages frame-by-frame animations with customizable timing and display
 * @author Jay Lee
 *
 * Checked by Jason Chang, Arthur Mo
 */

#include <QWidget>
#include <QImage>
#include <QVector>
#include <QTimer>

/**
 * @class Animation
 * @brief Handles the display and playback of frame-based animations
 * @details Provides functionality for adding, displaying, and animating frames in a widget
 */
class Animation : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructor for the Animation widget
     * @param parent The parent widget
     */
    explicit Animation(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the Animation widget
     */
    ~Animation();

    /**
     * @brief Adds a frame to the animation sequence
     * @param frame The image to add as a frame
     */
    void addFrame(const QImage &frame);

    /**
     * @brief Removes all frames from the animation
     */
    void clearFrames();

    /**
     * @brief Displays a single frame without animation
     * @param frame The image to display
     */
    void showSingleFrame(const QImage &frame);

    /**
     * @brief Starts the animation playback
     */
    void play();

    /**
     * @brief Stops the animation playback
     */
    void stop();

    /**
     * @brief Sets the frame rate of animation playback
     * @param frame rate to set
     */
    void setFrameRate(int fps);

protected:
    /**
     * @brief Handles the paint event for rendering frames
     * @param event The paint event
     */
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<QImage> m_frames;          // List of frames
    int m_currentFrameIndex;           // Current frame being displayed
    int m_fps;
    QTimer m_timer;                    // Timer for frame switching

private slots:
    /**
     * @brief Updates to the next frame in the animation sequence
     */
    void updateFrame();
};

#endif // ANIMATION_H
