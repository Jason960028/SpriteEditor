#include "SpriteEditorControl.h"
#include "SpriteEditorModel.h"

SpriteEditorController::SpriteEditorController(SpriteEditorModel* model, QObject* parent)
    : QObject(parent),
    m_model(model),
    m_currentTool(Tools::ToolType::Pen)
{
    // Initialize controller with model reference
}

void SpriteEditorController::addFrame()
{
    if (m_model) {
        m_model->addFrame();
        emit frameListChanged(m_model->getCurrentIndex());
    }
}

void SpriteEditorController::removeCurrentFrame()
{
    if (m_model && m_model->getFramesListSize() > 1) {
        m_model->removeFrame();
        emit frameListChanged(m_model->getCurrentIndex());
    }
}

void SpriteEditorController::handlePlayPressed()
{
    if (m_model && m_model->getFramesListSize() > 1) {
        emit animationStateChanged(true);
        // Actual animation logic would go here
    }
}

void SpriteEditorController::handleStopPressed()
{
    emit animationStateChanged(false);
}

void SpriteEditorController::handleFrameSelected(int index) {
    if (m_model) {
        m_model->setCurrentFrame(index);
        emit frameListChanged(index);
    }
}

void SpriteEditorController::moveFrameUp(int index) {
    if (m_model && index > 0) {
        m_model->moveFrameUp(index);
        emit frameListChanged(index - 1);
    }
}

void SpriteEditorController::moveFrameDown(int index) {
    if (m_model && index < m_model->getFramesListSize() - 1) {
        m_model->moveFrameDown(index);
        emit frameListChanged(index + 1);
    }
}

void SpriteEditorController::onPenClicked() {
    if (m_model) {
        m_model->setCurrentTool(Tools::ToolType::Pen);
    }
}

void SpriteEditorController::onEraserClicked() {
    if (m_model) {
        m_model->setCurrentTool(Tools::ToolType::Eraser);
    }
}

void SpriteEditorController::onFillClicked() {
    if (m_model) {
        m_model->setCurrentTool(Tools::ToolType::Fill);
    }
}
