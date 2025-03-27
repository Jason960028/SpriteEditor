#include "spriteEditorModel.h"
#include <QFile>
#include <QDebug>

spriteEditorModel::spriteEditorModel()
{
    // Initialization if necessary
}

void spriteEditorModel::loadSprite(const QString& fileName)
{
    // Implement loading logic here
    qDebug() << "Loading sprite from " << fileName;
}

void spriteEditorModel::saveSprite(const QString& fileName)
{
    // Implement saving logic here
    qDebug() << "Saving sprite to " << fileName;
}



















