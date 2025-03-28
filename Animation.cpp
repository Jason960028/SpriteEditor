#include "Animation.h"
#include <QPainter>

Animation::Animation(QWidget *parent)
    : QWidget(parent),
    m_currentFrameIndex(0),
    m_frameDelay(100) // Default frame delay: 100ms (~10 FPS)
{
    // Connect timer to frame update function
    connect(&m_timer, &QTimer::timeout, this, &Animation::updateFrame);
}

Animation::~Animation()
{
    stop();
}

void Animation::addFrame(const QImage &frame)
{
    // Add a new frame and refresh the display
    m_frames.append(frame);
    update();
}

void Animation::clearFrames()
{
    // Stop animation and clear all frames
    stop();
    m_frames.clear();
    m_currentFrameIndex = 0;
    update();
}

void Animation::showSingleFrame(const QImage &frame)
{
    // Stop animation and display only a single frame (used for preview)
    stop();
    m_frames.clear();
    m_frames.append(frame);
    m_currentFrameIndex = 0;
    update();
}

void Animation::play()
{
    // Start the animation if not already running
    if (!m_timer.isActive() && !m_frames.isEmpty()) {
        m_timer.start(m_frameDelay);
    }
}

void Animation::stop()
{
    // Stop the animation timer
    if (m_timer.isActive()) {
        m_timer.stop();
    }
}

void Animation::setFrameDelay(int delay)
{
    // Update delay between frames and restart the timer if necessary
    m_frameDelay = delay;
    if (m_timer.isActive()) {
        m_timer.start(m_frameDelay);
    }
}

void Animation::updateFrame()
{
    // Advance to the next frame and repaint the widget
    if (m_frames.isEmpty())
        return;
    
    m_currentFrameIndex = (m_currentFrameIndex + 1) % m_frames.size();
    update();
}

void Animation::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    
    // Fill background
    painter.fillRect(rect(), Qt::gray);
    
    if (!m_frames.isEmpty()) {
        // Draw the current frame, scaled and centered
        const QImage &currentFrame = m_frames[m_currentFrameIndex];
        QImage scaled = currentFrame.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QPoint center = rect().center() - QPoint(scaled.width() / 2, scaled.height() / 2);
        painter.drawImage(center, scaled);
    } else {
        // If no frames are available, show placeholder text
        painter.setPen(Qt::black);
        painter.drawText(rect(), Qt::AlignCenter, "No frames to display");
    }
}
#include "Animation.h"

animation::animation() {}
