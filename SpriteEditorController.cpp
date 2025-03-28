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
        emit frameListChanged(m_model->getFramesListSize());
        qDebug() << "Frame added";
        qDebug() << "Frame size " << m_model->getFramesListSize();
    }


}

void SpriteEditorController::removeCurrentFrame()
{
    if (m_model && m_model->getFramesListSize() > 1) {
        m_model->removeFrame();
        emit frameListChanged(m_model->getFramesListSize());
        qDebug() << "Frame deleted";
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
    qDebug() << "Frame moved up";
    emit currentFrameChanged();
}

void SpriteEditorController::moveFrameDown(int index){
    m_model->setCurrentFrame(index+1);
    m_model->moveFrameDown(index);
    qDebug() << "Frame moved down";
    emit currentFrameChanged();
}


void SpriteEditorController::onPenClicked(){

    m_model->setCurrentTool(Tools::ToolType::Pen);
    m_currentTool = m_model->getCurrentTool();
    emit toolSelectSignal(m_currentTool);
}

void SpriteEditorController::onEraserClicked(){
    qDebug() << "Eraser set";
    m_model->setCurrentTool(Tools::ToolType::Eraser);
    m_currentTool = m_model->getCurrentTool();
    emit toolSelectSignal(m_currentTool);
}
