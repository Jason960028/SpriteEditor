#include "spriteEditorView.h"
#include <QToolBar>
#include <QToolButton>
#include <QButtonGroup>
#include <QMessageBox>
#include "SpriteEditorModel.h"
#include "ui_SpriteEditorView.h"
#include "canvas.h"
#include "QVBoxLayout"

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


    // Set up layout for CanvasFrame
    QVBoxLayout* canvasLayout = new QVBoxLayout(ui->Canvas);
    canvasLayout->setContentsMargins(0, 0, 0, 0);
    canvasLayout->addWidget(m_canvas);

    // Set layout policy to Fixed to maintain exact Canvas size
    m_canvas->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // Get canvas dimensions through accessors
    int canvasWidth = m_canvas->getCanvasWidth();
    int canvasHeight = m_canvas->getCanvasHeight();

    // Adjust size to display the grid with scaling
    int pixelScale = 10;
    m_canvas->setFixedSize(canvasWidth * pixelScale, canvasHeight * pixelScale);


    // Update canvas with initial frame
    m_canvas->updateCanvas(m_currentFrame);

    updateFrameList(m_model->getCurrentIndex());
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
    connect(ui->moveUpFrameButton, &QToolButton::clicked, this, &SpriteEditorView::onMoveUpClicked);
    connect(ui->moveDownFrameButton, &QToolButton::clicked, this, &SpriteEditorView::onMoveDownClicked);

    // Canvas updates
    connect(m_controller, &SpriteEditorController::currentFrameChanged, this, &SpriteEditorView::handleFrameChanged);

    // Add frame update
    connect(m_addFrameButton, &QToolButton::clicked, m_controller, &SpriteEditorController::addFrame);
    // delete frame update
    connect(m_deleteFrameButton, &QToolButton::clicked, m_controller, &SpriteEditorController::removeCurrentFrame);
    // frame list update
    connect(m_controller, &SpriteEditorController::frameListChanged, this, &SpriteEditorView::updateFrameList);

    connect(m_controller, &SpriteEditorController::toolSelectSignal, this, &SpriteEditorView::updateToolButtonStates);

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
    connect(m_frameList, &QListWidget::currentRowChanged,
            this, &SpriteEditorView::onFrameSelectionChanged);

    // Connect canvas interaction signals
    connect(m_canvas, &Canvas::mousePressed, this, &SpriteEditorView::handleMousePressed);
    connect(m_canvas, &Canvas::mouseDragged, this, &SpriteEditorView::handleMouseDragged);
    connect(m_canvas, &Canvas::mouseReleased, this, &SpriteEditorView::handleMouseReleased);

}

void SpriteEditorView::updateFrameList(int currentIndex){
    ui->frameListWidget->blockSignals(true);

    ui->frameListWidget->clear();
    for (int i = 0; i < m_model->getFramesListSize(); ++i) {
        QListWidgetItem *item = new QListWidgetItem(
            QString("Frame %1").arg(i+1),
            ui->frameListWidget
            );
        item->setIcon(QIcon(":/icons/frame.png"));
    }


    // Set current selection
    ui->frameListWidget->setCurrentRow(currentIndex);
    // Restore signal handling
    ui->frameListWidget->blockSignals(false);

}

void SpriteEditorView::onAddFrameClicked()
{
    emit addFrameRequested();
}

void SpriteEditorView::onDeleteFrameClicked()
{
    int index = m_model->getCurrentIndex();
    if (index >= 0) {
        emit deleteFrameRequested(index);
    }
    updateCanvasDisplay();
}

void SpriteEditorView::onMoveUpClicked()
{
    int index = m_model->getCurrentIndex();
    if (index > 0) {
        emit moveFrameUpRequested(index);
        ui->frameListWidget->setCurrentRow(index-1);

    }
}

void SpriteEditorView::onMoveDownClicked()
{
    int index = m_model->getCurrentIndex();
    if (index >= 0 && index < ui->frameListWidget->count()-1) {
        emit moveFrameDownRequested(index);
        ui->frameListWidget->setCurrentRow(index+1);

    }
}

void SpriteEditorView::handleFrameChanged(){
    updateFrameList(m_model->getCurrentIndex());
    updateCanvasDisplay();
}

void SpriteEditorView::handleMousePressed(const QPoint& pos) {
    if (pos.x() >= 0 && pos.y() >= 0) {
        Tools::applyTool(m_model->getCurrentFrame(), pos, m_currentTool, m_currentColor);
        updateCanvasDisplay();
    }
}

void SpriteEditorView::handleMouseDragged(const QPoint& pos) {
    if (pos.x() >= 0 && pos.y() >= 0) {
        Tools::applyTool(m_model->getCurrentFrame(), pos, m_currentTool, m_currentColor);
        updateCanvasDisplay();
    }
}

void SpriteEditorView::handleMouseReleased(const QPoint& pos) {
    if (pos.x() >= 0 && pos.y() >= 0) {
        Tools::applyTool(m_model->getCurrentFrame(), pos, m_currentTool, m_currentColor);
        updateCanvasDisplay();
    }
}

void SpriteEditorView::updateCanvasDisplay() {
    m_canvas->updateCanvas(m_model->getCurrentFrame());
    ui->frameListWidget->setCurrentRow(m_model->getCurrentIndex());
}

void SpriteEditorView::onFrameSelectionChanged()
{
    int selectedRow = m_frameList->currentRow();
    qDebug() << "current row changed";
    if (selectedRow >= 0) {
        emit frameSelected(selectedRow);
    }
    updateCanvasDisplay();

}

void SpriteEditorView::updateToolButtonStates() {
    // Uncheck all tool buttons
    ui->Pen->setChecked(false);
    ui->Eraser->setChecked(false);
    ui->Fill->setChecked(false);
    m_currentTool = m_model->getCurrentTool();

    // Check the button for the current tool
    switch (m_currentTool) {
    case Tools::ToolType::Pen:
        qDebug() << "Pen checked";
        ui->Pen->setChecked(true);
        break;
    case Tools::ToolType::Eraser:
        qDebug() << "Eraser checked";
        ui->Eraser->setChecked(true);
        break;
    case Tools::ToolType::Fill:
        qDebug() << "fill checked";
        ui->Fill->setChecked(true);
        break;
    }
}
