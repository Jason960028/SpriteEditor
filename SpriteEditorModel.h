#ifndef SPRITEEDITORMODEL_H
#define SPRITEEDITORMODEL_H
#include <Qstring>

class spriteEditorModel
{
public:
    spriteEditorModel();

    // Add methods for model logic here, e.g., loading and saving sprites.
    void loadSprite(const QString& fileName);
    void saveSprite(const QString& fileName);

private:
         // You can store sprite data here (e.g., QImage or other structures)
};

#endif // SPRITEEDITORMODEL_H

