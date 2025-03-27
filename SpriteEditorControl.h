#ifndef SPRITEEDITORCONTROLLER_H
#define SPRITEEDITORCONTROLLER_H

#include <QObject>
#include <QWidget>

class spriteEditorModel; // Forward declaration of the spriteEditorModel class

class spriteEditorController : public QObject
{
    Q_OBJECT

public:
    explicit spriteEditorController(spriteEditorModel* model, QObject* parent = nullptr, QWidget* parentWidget = nullptr);

public slots:
    void onLoadClicked();
    void onSaveClicked();

private:
    spriteEditorModel* m_model;
    QWidget* m_parentWidget;
};

#endif // SPRITEEDITORCONTROLLER_H

