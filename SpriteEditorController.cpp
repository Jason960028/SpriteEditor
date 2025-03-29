#include "SpriteEditorController.h"
#include "SpriteEditorModel.h"

SpriteEditorController::SpriteEditorController(SpriteEditorModel* model, QObject* parent)
    : QObject(parent),
    m_model(model),
    m_currentTool(Tools::ToolType::Pen)
{

}

void SpriteEditorController::addFrame()
{
    if (m_model) {
        m_model->addFrame();
        m_model->setCurrentFrame(m_model->getFramesListSize()-1);
        emit frameListChanged(m_model->getFramesListSize());
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

void SpriteEditorController::handleFrameSelected(int index){
    m_model->setCurrentFrame(index);
}

void SpriteEditorController::moveFrameUp(int index){
    m_model->setCurrentFrame(index-1);
    m_model->moveFrameUp(index);
    emit currentFrameChanged();
}

void SpriteEditorController::moveFrameDown(int index){
    m_model->setCurrentFrame(index+1);
    m_model->moveFrameDown(index);
    emit currentFrameChanged();
}


void SpriteEditorController::onPenClicked(){

    m_model->setCurrentTool(Tools::ToolType::Pen);
    m_currentTool = m_model->getCurrentTool();
    emit toolSelectSignal(m_currentTool);
}

void SpriteEditorController::onEraserClicked(){
    m_model->setCurrentTool(Tools::ToolType::Eraser);
    m_currentTool = m_model->getCurrentTool();
    emit toolSelectSignal(m_currentTool);
}

void SpriteEditorController::onFillingClicked(){
    m_model->setCurrentTool(Tools::ToolType::Fill);
    m_currentTool = m_model->getCurrentTool();
    emit toolSelectSignal(m_currentTool);
}
