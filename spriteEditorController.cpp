#include "spriteEditorController.h"
#include "spriteEditorModel.h"

spriteEditorController::spriteEditorController(spriteEditorModel* model, QObject* parent)
    : QObject(parent),
    m_model(model),
    m_activeTool(nullptr)
{
    // Initialize with default tool
    setActiveTool(Tools::Pen);
}

void spriteEditorController::setActiveTool(Tools::Type toolType)
{
    if (m_activeTool && m_activeTool->type() == toolType) {
        return;
    }

    // setting the current tool
    Tools::setCurrentTool(toolType);

    // assigned the current tool
    m_activeTool = Tools::currentTool();
    emit toolChanged(toolType);
}

// connect to Canvas mouse clicked signal
void spriteEditorController::handlePixelClick(int x, int y)
{
    m_model->setPixel(x, y);
}

void spriteEditorController::handlePixelDrag(int x, int y)
{
    handlePixelClick(x, y); // Reuse same logic for drag
}

void spriteEditorController::addFrame()
{
    if (m_model) {
        m_model->addFrame();
    }
}

void spriteEditorController::removeCurrentFrame()
{
    if (m_model && m_model->frameCount() > 1) {
        m_model->removeFrame();
    }
}

void spriteEditorController::playAnimation()
{
    if (m_model && m_model->frameCount() > 1) {
        emit animationStateChanged(true);
        // Actual animation logic would go here
    }
}

void spriteEditorController::stopAnimation()
{
    emit animationStateChanged(false);
    // Actual animation stop logic would go here
}

void spriteEditorController::onPenClicked(){

    Tools::setCurrentTool(Tools::Pen);
    m_activeTool = Tools::currentTool();
    emit toolChanged(Tools::Pen);  // Notify view

    // Update model's drawing color if needed
    m_model->setCurrentColor(Qt::black);  // Example pen color
}
