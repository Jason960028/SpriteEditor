#ifndef TOOLS_H
#define TOOLS_H

#include <QObject>
#include <QMap>
#include <QIcon>

class spriteEditorModel;

class Tools : public QObject
{
    Q_OBJECT
public:
    enum Type { Pen, Eraser };
    Q_ENUM(Type)

    explicit Tools(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~Tools() = default;

    virtual void apply(spriteEditorModel* model, const QPoint& pos) = 0;
    virtual void begin(spriteEditorModel* model, const QPoint& pos);
    virtual void move(spriteEditorModel* model, const QPoint& pos);
    virtual void end(spriteEditorModel* model, const QPoint& pos);

    virtual Type type() const = 0;
    virtual QIcon icon() const = 0;
    virtual QString name() const = 0;
    virtual QString shortcut() const = 0;

    // Tool management
    static Tools* currentTool();
    static void setCurrentTool(Type toolType);
    static Tools* getTool(Type toolType);

private:
    static QMap<Type, Tools*> m_tools;
    static Tools* m_currentTool;
};

#endif // TOOL_H
