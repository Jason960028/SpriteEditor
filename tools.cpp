#include "tools.h"
#include <QPainter>
#include "spriteEditorModel.h"


// Static tool instances
QMap<Tools::Type, Tools*> Tools::m_tools;
Tools* Tools::m_currentTool = nullptr;


// Pen Tool Implementation
class PenTool : public Tools
{
public:
    explicit PenTool(QObject* parent = nullptr) : Tools(parent) {}

    void apply(spriteEditorModel* model, const QPoint& pos) override {
        if (model){
            model->setPixel(pos.x(), pos.y(), model->currentColor());
        }

    }

    void begin(spriteEditorModel* model, const QPoint& pos) override {
    }


    void end(spriteEditorModel*, const QPoint&) override {}

    Type type() const override { return Pen; }
    QIcon icon() const override { return QIcon(":/icons/pen.png"); }
    QString name() const override { return tr("Pen"); }
    QString shortcut() const override { return "P"; }

private:
    QPoint m_lastPos;
};


// Eraser Tool Implementation
class EraserTool : public Tools
{
public:
    explicit EraserTool(QObject* parent = nullptr) : Tools(parent) {}

    void apply(spriteEditorModel* model, const QPoint& pos) override{
    }

    void begin(spriteEditorModel* model, const QPoint& pos) override{

    }

    void end(spriteEditorModel*, const QPoint&) override {}

    Type type() const override { return Eraser; }
    QIcon icon() const override { return QIcon(":/icons/eraser.png"); }
    QString name() const override { return tr("Eraser"); }
    QString shortcut() const override { return "E"; }

private:
    QPoint m_lastPos;
};

// Tool Management

Tools* Tools::currentTool() {
    if (!m_currentTool) {
        // Initialize tools if not done yet
        if (m_tools.isEmpty()) {
            m_tools[Pen] = new PenTool();
            m_tools[Eraser] = new EraserTool();
        }
        setCurrentTool(Pen); // Default to pen
    }
    return m_currentTool;
}

void Tools::setCurrentTool(Type toolType) {
    if (m_tools.isEmpty()) {
        m_tools[Pen] = new PenTool();
        m_tools[Eraser] = new EraserTool();
    }
    m_currentTool = m_tools.value(toolType, m_tools[Pen]);
}

Tools* Tools::getTool(Type toolType) {
    if (m_tools.isEmpty()) {
        m_tools[Pen] = new PenTool();
        m_tools[Eraser] = new EraserTool();
    }
    return m_tools.value(toolType, m_tools[Pen]); // if toolType is not exist, return Pen
}
