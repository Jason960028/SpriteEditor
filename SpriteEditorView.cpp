#include "SpriteEditorView.h"
#include <QToolBar>
#include <QToolButton>
#include <QButtonGroup>
#include <QMessageBox>
#include <QVBoxLayout>
#include "SpriteEditorModel.h"
#include "SpriteEditorControl.h"
#include "ui_SpriteEditorView.h"
#include "Canvas.h"

SpriteEditorView::SpriteEditorView(SpriteEditorModel* model,
                                   SpriteEditorController* controller,
                                   QWidget* parent)
    : QMainWindow(parent),
    ui(new Ui::SpriteEditorView),
    m_model(model),
    m_controller(controller),
    m_currentTool(Tools::ToolType::Pen),
    m_currentFrame(m_model->getCurrentFrame()),
    m_currentColor(m_model->getCurrentColor())
{
    ui->setupUi(this);

    // Initialize UI references
    m_penButton = findChild<QToolButton*>("Pen");
    m_eraserButton = findChild<QToolButton*>("Eraser");
    m_fillButton = findChild<QToolButton*>("Fill");

    m_addFrameButton = ui->AddFrame;
    m_deleteFrameButton = ui->DeleteFrame;
    m_frameList = ui->frameListWidget;

    // Create the canvas with model reference
    m_canvas = new Canvas(this, m_model);

    // Connect signals and set up layout
    setupUI();
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

    // Initialize frame list with current frames
    updateFrameList();
}

SpriteEditorView::~SpriteEditorView()
{
    delete ui;
}

void SpriteEditorView::setupUI()
{
    // Any additional UI setup can go here
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
    if (m_fillButton) {
        connect(m_fillButton, &QToolButton::clicked, m_controller, &SpriteEditorController::onFillClicked);
    }

    // Frame management updates
    connect(m_model, &SpriteEditorModel::frameChanged, this, &SpriteEditorView::handleFrameChanged);
    connect(m_model, &SpriteEditorModel::framesUpdated, this, &SpriteEditorView::updateFrameList);
    connect(m_model, &SpriteEditorModel::frameListChanged, this, &SpriteEditorView::updateFrameListSelection);

    // Frame management buttons
    connect(m_addFrameButton, &QToolButton::clicked, this, &SpriteEditorView::onAddFrameClicked);
    connect(m_deleteFrameButton, &QToolButton::clicked, this, &SpriteEditorView::onDeleteFrameClicked);
    connect(ui->moveUpFrameButton, &QToolButton::clicked, this, &SpriteEditorView::onMoveUpClicked);
    connect(ui->moveDownFrameButton, &QToolButton::clicked, this, &SpriteEditorView::onMoveDownClicked);

    // Frame selection from list widget
    connect(m_frameList, &QListWidget::currentRowChanged, this, &SpriteEditorView::onFrameSelectionChanged);

    // Action forwarding
    connect(this, &SpriteEditorView::addFrameRequested, m_controller, &SpriteEditorController::addFrame);
    connect(this, &SpriteEditorView::deleteFrameRequested, m_controller, &SpriteEditorController::removeCurrentFrame);
    connect(this, &SpriteEditorView::moveFrameUpRequested, m_controller, &SpriteEditorController::moveFrameUp);
    connect(this, &SpriteEditorView::moveFrameDownRequested, m_controller, &SpriteEditorController::moveFrameDown);
    connect(this, &SpriteEditorView::frameSelected, m_controller, &SpriteEditorController::handleFrameSelected);

    // Canvas interaction signals
    connect(m_canvas, &Canvas::mousePressed, this, &SpriteEditorView::handleMousePressed);
    connect(m_canvas, &Canvas::mouseDragged, this, &SpriteEditorView::handleMouseDragged);
    connect(m_canvas, &Canvas::mouseReleased, this, &SpriteEditorView::handleMouseReleased);
}

void SpriteEditorView::updateFrameList()
{
    // Store current selection to restore after update
    int currentIndex = m_model->getCurrentIndex();

    // Clear and rebuild the list
    m_frameList->clear();

    for (int i = 0; i < m_model->getFramesListSize(); ++i) {
        QListWidgetItem *item = new QListWidgetItem(
            QString("Frame %1").arg(i+1),
            m_frameList
            );
        item->setIcon(QIcon(":/icons/frame.png"));
    }

    // Restore selection if it's valid
    if (currentIndex >= 0 && currentIndex < m_frameList->count()) {
        m_frameList->blockSignals(true);
        m_frameList->setCurrentRow(currentIndex);
        m_frameList->blockSignals(false);
    }

    // Update the current frame
    m_currentFrame = m_model->getCurrentFrame();
    updateCanvasDisplay();
}

void SpriteEditorView::updateFrameListSelection()
{
    int currentIndex = m_model->getCurrentIndex();
    if (currentIndex >= 0 && currentIndex < m_frameList->count()) {
        m_frameList->blockSignals(true);
        m_frameList->setCurrentRow(currentIndex);
        m_frameList->blockSignals(false);

        // Update current frame and canvas display
        m_currentFrame = m_model->getCurrentFrame();
        updateCanvasDisplay();
    }
}

void SpriteEditorView::onAddFrameClicked()
{
    emit addFrameRequested();
}

void SpriteEditorView::onDeleteFrameClicked()
{
    if (m_model->getFramesListSize() > 1) {
        int index = m_model->getCurrentIndex();
        emit deleteFrameRequested(index);
    }
}

void SpriteEditorView::onMoveUpClicked()
{
    int index = m_model->getCurrentIndex();
    if (index > 0) {
        emit moveFrameUpRequested(index);
    }
}

void SpriteEditorView::onMoveDownClicked()
{
    int index = m_model->getCurrentIndex();
    if (index >= 0 && index < m_model->getFramesListSize() - 1) {
        emit moveFrameDownRequested(index);
    }
}

void SpriteEditorView::onFrameSelectionChanged(int row)
{
    if (row >= 0 && row < m_model->getFramesListSize()) {
        emit frameSelected(row);
        m_currentFrame = m_model->getCurrentFrame();
        updateCanvasDisplay();
    }
}

void SpriteEditorView::handleFrameChanged()
{
    m_currentFrame = m_model->getCurrentFrame();
    updateCanvasDisplay();
}

void SpriteEditorView::handleMousePressed(const QPoint& pos)
{
    if (pos.x() >= 0 && pos.y() >= 0) {
        m_currentTool = m_model->getCurrentTool();
        m_currentColor = m_model->getCurrentColor();

        // Apply tool based on current tool type
        if (m_currentTool == Tools::ToolType::Pen) {
            m_model->setPixel(pos.x(), pos.y());
        }
        else if (m_currentTool == Tools::ToolType::Eraser) {
            // Add this method to SpriteEditorModel
            m_model->erasePixel(pos.x(), pos.y());
        }
        else if (m_currentTool == Tools::ToolType::Fill) {
            // Add this method to SpriteEditorModel
            m_model->fillArea(pos.x(), pos.y());
        }

        // Get the updated frame from the model
        m_currentFrame = m_model->getCurrentFrame();
        updateCanvasDisplay();
    }
}

void SpriteEditorView::handleMouseDragged(const QPoint& pos)
{
    if (pos.x() >= 0 && pos.y() >= 0) {
        m_currentTool = m_model->getCurrentTool();
        m_currentColor = m_model->getCurrentColor();

        // Apply tool based on current tool type
        if (m_currentTool == Tools::ToolType::Pen) {
            m_model->setPixel(pos.x(), pos.y());
        }
        else if (m_currentTool == Tools::ToolType::Eraser) {
            m_model->erasePixel(pos.x(), pos.y());
        }
        // Fill tool usually not applied during dragging

        // Get the updated frame from the model
        m_currentFrame = m_model->getCurrentFrame();
        updateCanvasDisplay();
    }
}


void SpriteEditorView::handleMouseReleased(const QPoint& pos)
{
    // Handle the same way as mouse dragged
    handleMouseDragged(pos);
}


void SpriteEditorView::updateCanvasDisplay()
{
    m_canvas->updateCanvas(m_currentFrame);
}


