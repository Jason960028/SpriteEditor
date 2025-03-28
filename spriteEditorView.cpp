#include "spriteEditorView.h"
#include <QToolBar>
#include <QToolButton>
#include <QButtonGroup>
#include <QMessageBox>
#include "spriteEditorModel.h"
#include "ui_SpriteEditorView.h"
#include "canvas.h"

SpriteEditorView::SpriteEditorView(SpriteEditorModel* model,
                                   SpriteEditorController* m_controller,
                                   QWidget* parent)
    : QMainWindow(parent),
    ui(new Ui::SpriteEditorView),
    m_model(model),
    m_controller(m_controller),
    //m_canvasWidget(new canvas(this)),
    m_currentTool(Tools::ToolType::Pen),
    m_currentFrame(m_model->getCurrentFrame()),
    m_currentColor(m_model->getCurrentColor())
{
    ui->setupUi(this);
    m_penButton = findChild<QToolButton*>("Pen");
    m_eraserButton = findChild<QToolButton*>("Eraser");

    m_addFrameButton = ui->AddFrame;
    m_deleteFrameButton = ui->DeleteFrame;

    m_canvas = new Canvas(this, m_model);
    setupUI();
    m_frameList = ui->frameListWidget;
    connectSignals();
}

SpriteEditorView::~SpriteEditorView()
{
    delete ui;
}

void SpriteEditorView::setupUI()
{

}

void SpriteEditorView::setupTools()
{
    m_currentTool = m_model->getCurrentTool();
}

void SpriteEditorView::connectSignals()
{
    // Tool buttons
    connect(m_penButton, &QToolButton::clicked, m_controller, &SpriteEditorController::onPenClicked);
    connect(m_eraserButton, &QToolButton::clicked, m_controller, &SpriteEditorController::onEraserClicked);

    // Canvas updates
    connect(m_model, &SpriteEditorModel::frameChanged, this, &SpriteEditorView::handleFrameChanged);

    // Add frame update
    connect(m_addFrameButton, &QToolButton::clicked, m_controller, &SpriteEditorController::addFrame);
    // delete frame update
    connect(m_deleteFrameButton, &QToolButton::clicked, m_controller, &SpriteEditorController::removeCurrentFrame);
    // frame list update
    connect(m_controller, &SpriteEditorController::frameListChanged, this, &SpriteEditorView::updateFrameList);

    // In your main window or m_controller
    connect(this, &SpriteEditorView::addFrameRequested,
            m_controller, &SpriteEditorController::addFrame);
    connect(this, &SpriteEditorView::deleteFrameRequested,
            m_controller, &SpriteEditorController::removeCurrentFrame);
    connect(this, &SpriteEditorView::moveFrameUpRequested,
            m_controller, &SpriteEditorController::moveFrameUp);
    connect(this, &SpriteEditorView::moveFrameDownRequested,
            m_controller, &SpriteEditorController::moveFrameDown);
    connect(this, &SpriteEditorView::frameSelected,
            m_controller, &SpriteEditorController::handleFrameSelected);


    // Connect canvas interaction signals
    connect(m_canvas, &Canvas::mousePressed, this, &SpriteEditorView::handleMousePressed);
    connect(m_canvas, &Canvas::mouseDragged, this, &SpriteEditorView::handleMouseDragged);
    connect(m_canvas, &Canvas::mouseReleased, this, &SpriteEditorView::handleMouseReleased);

}

void SpriteEditorView::updateFrameList(int currentIndex){
    ui->frameListWidget->clear();

    for (int i = 0; i < m_model->getFramesListSize(); ++i) {
        QListWidgetItem *item = new QListWidgetItem(
            QString("Frame %1").arg(i+1),
            ui->frameListWidget
            );
        item->setIcon(QIcon(":/icons/frame.png"));
    }

    // Block signals temporarily to prevent spurious emissions
    ui->frameListWidget->blockSignals(true);
    // Set current selection
    ui->frameListWidget->setCurrentRow(currentIndex);
    // Restore signal handling
    ui->frameListWidget->blockSignals(false);

}

void SpriteEditorView::onAddFrameClicked()
{
    emit addFrameRequested();
    updateFrameList(m_model->getCurrentIndex());
}

void SpriteEditorView::onDeleteFrameClicked()
{
    int index = m_model->getCurrentIndex();
    if (index >= 0) {
        emit deleteFrameRequested(index);
        updateFrameList(m_model->getCurrentIndex());
    }
}

void SpriteEditorView::onMoveUpClicked()
{
    int index = m_model->getCurrentIndex();
    if (index > 0) {
        emit moveFrameUpRequested(index);
        updateFrameList(index-1);
    }
}

void SpriteEditorView::onMoveDownClicked()
{
    int index = m_model->getCurrentIndex();
    if (index >= 0 && index < ui->frameListWidget->count()-1) {
        emit moveFrameDownRequested(index);
        updateFrameList(index+1);
    }
}

void SpriteEditorView::handleFrameChanged(){
    updateCanvasDisplay();
}

void SpriteEditorView::handleMousePressed(const QPoint& pos) {
    if (pos.x() >= 0 && pos.y() >= 0) {
        Tools::applyTool(m_currentFrame, pos, m_currentTool, m_currentColor);
        updateCanvasDisplay();
    }
}

void SpriteEditorView::handleMouseDragged(const QPoint& pos) {
    if (pos.x() >= 0 && pos.y() >= 0) {
        Tools::applyTool(m_currentFrame, pos, m_currentTool, m_currentColor);
        updateCanvasDisplay();
    }
}

void SpriteEditorView::handleMouseReleased(const QPoint& pos) {
    if (pos.x() >= 0 && pos.y() >= 0) {
        Tools::applyTool(m_currentFrame, pos, m_currentTool, m_currentColor);
        updateCanvasDisplay();
    }
}

void SpriteEditorView::updateCanvasDisplay() {
    m_canvas->updateCanvas(m_currentFrame);
}

void SpriteEditorView::onFrameSelectionChanged()
{
    int selectedRow = ui->frameListWidget->currentRow();
    if (selectedRow >= 0) {
        emit frameSelected(selectedRow);
    }
}












