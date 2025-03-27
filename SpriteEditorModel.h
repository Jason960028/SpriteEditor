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

private:
    std::vector<QImage> m_frames;
};

#endif // SPRITEEDITORMODEL_H

