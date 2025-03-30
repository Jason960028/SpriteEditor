#include "SpriteEditorController.h"
#include "SpriteEditorModel.h"
#include "SpriteEditorView.h"
#include <QMessageBox>
#include <QPushButton>


SpriteEditorController::SpriteEditorController(SpriteEditorModel* model, QObject* parent)
    : QObject(parent),
    m_model(model),
    m_currentTool(Tools::ToolType::Pen)
{

}

void SpriteEditorController::setView(SpriteEditorView* view) {
    m_view = view;
    connect(m_view, &SpriteEditorView::loadClicked, this, &SpriteEditorController::onLoadClicked);
    connect(m_view, &SpriteEditorView::saveClicked, this, &SpriteEditorController::onSaveClicked);
}

void SpriteEditorController::addFrame()
{
    if (m_model) {

        //User selction message box
        QMessageBox msgBox(m_view);
        msgBox.setWindowTitle(tr("Add Frame"));
        msgBox.setText(tr("Choose an option?"));
        QPushButton *emptyButton = msgBox.addButton(tr("Empty Frame"), QMessageBox::ActionRole);
        QPushButton *duplicateButton = msgBox.addButton(tr("Copy Current frame"), QMessageBox::ActionRole);
        msgBox.setDefaultButton(emptyButton);

        msgBox.exec();

        if (msgBox.clickedButton() == duplicateButton) {
            // Copy current frame
            m_model->duplicateFrame(m_model->getCurrentIndex());
        } else {
            // Add empty frame
            m_model->addFrame();
        }

        m_model->setCurrentFrame(m_model->getFramesListSize()-1);
        emit frameListChanged(m_model->getFramesListSize());
        qDebug() << "Frame added";
        qDebug() << "Frame size " << m_model->getFramesListSize();
    }
}

void SpriteEditorController::removeCurrentFrame()
{
    if (m_model && m_model->getFramesListSize() > 1) {
        m_model->removeFrame();
        emit frameListChanged(m_model->getCurrentIndex());
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
    m_model->setCurrentTool(Tools::ToolType::Eraser);
    m_currentTool = m_model->getCurrentTool();
    emit toolSelectSignal(m_currentTool);
}

void SpriteEditorController::onFillingClicked(){
    m_model->setCurrentTool(Tools::ToolType::Fill);
    m_currentTool = m_model->getCurrentTool();
    emit toolSelectSignal(m_currentTool);
}

void SpriteEditorController::onLoadClicked() {
    QString fileName = QFileDialog::getOpenFileName(
        m_view,  // the QWidget* view passed in
        tr("Open SSP File"),
        "",
        tr("SSP Files (*.ssp)")
        );

    if (!fileName.isEmpty()) {
        // Call load function that is inside the model
        m_model->loadSprite(fileName);
    }
}

void SpriteEditorController::onSaveClicked(){

    QString fileName = QFileDialog::getSaveFileName(
        m_view,
        tr("Save File"),
        "", // Optional default filename, e.g., "untitled.ssp"
        tr("Spreadsheet Files (*.ssp)")
        );

    if (!fileName.isEmpty()) {
        m_model->saveSprite(fileName);
    }
}

void SpriteEditorController::onColorSelected(const QColor& color) {
    if (m_model) {
        m_model->setCurrentColor(color);
    }
}

void SpriteEditorController::onFlipHorizontalClicked() {
    if (m_model) {
        m_model->flipHorizontal();
        emit currentFrameChanged();
    }
}

void SpriteEditorController::onCleanButtonClicked() {
    if (m_model) {
        m_model->clearCurrentFrame();
        emit currentFrameChanged();
    }
}
