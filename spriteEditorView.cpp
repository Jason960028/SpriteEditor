#include "spriteEditorView.h"
#include <QToolBar>
#include <QToolButton>
#include <QButtonGroup>
#include <QMessageBox>
#include "spriteEditorModel.h"
#include "ui_spriteEditorView.h"

spriteEditorView::spriteEditorView(spriteEditorModel* model,
                                   spriteEditorController* controller,
                                   QWidget* parent)
    : QMainWindow(parent),
    ui(new Ui::spriteEditorView),
    m_model(model),
    m_controller(controller),
    m_canvasWidget(new canvas(this)),
    m_penTool(nullptr),
    m_eraserTool(nullptr),
    m_activeTool(nullptr)
{
    ui->setupUi(this);
    m_penButton = findChild<QToolButton*>("Pen");
    m_eraserButton = findChild<QToolButton*>("Eraser");

    setupUI();
    setupTools();
    connectSignals();

    // Initialize with first frame
    if (m_model->frameCount() > 0) {
        m_canvas->setImage(m_model->getFrame(0));
    }
}

spriteEditorView::~spriteEditorView()
{
    delete m_penTool;
    delete m_eraserTool;
}

void spriteEditorView::setupUI()
{

}

void spriteEditorView::setupTools()
{
    // Create tools using factory
    //m_penTool = Tools::createTool(Tools::Pen, this);
    //m_eraserTool = Tools::createTool(Tools::Eraser, this);

    // Set default tool
    m_activeTool = m_penTool;
    //m_controller->setActiveTool(m_activeTool);
    m_penButton->setChecked(true);

    // Set button icons and text
    if (m_penTool) {
        m_penButton->setIcon(QIcon("icon.png"));
        m_penButton->setToolTip("Pen Tool");
    }
    if (m_eraserTool) {
        m_eraserButton->setIcon(QIcon("icon.png"));
        m_eraserButton->setToolTip("Eraser Tool");
    }
}

void spriteEditorView::connectSignals()
{
    // Tool buttons
    connect(m_penButton, &QToolButton::clicked, m_controller, &spriteEditorController::onPenClicked);
    connect(m_eraserButton, &QToolButton::clicked, m_controller, &spriteEditorController::onEraserClicked);

    // Frame buttons
    connect(m_addFrameButton, &QToolButton::clicked, this, &spriteEditorView::onAddFrameClicked);
    connect(m_removeFrameButton, &QToolButton::clicked, this, &spriteEditorView::onRemoveFrameClicked);

    // Animation buttons
    connect(m_playButton, &QToolButton::clicked, this, &spriteEditorView::onPlayClicked);
    connect(m_stopButton, &QToolButton::clicked, this, &spriteEditorView::onStopClicked);



    // Model updates
    connect(m_model, &spriteEditorModel::frameChanged, this, [this](int index) {
        //m_canvas->setImage(m_model->getFrame(index));
    });

    connect(m_model, &spriteEditorModel::framesUpdated, this, [this]() {
        bool hasFrames = m_model->frameCount() > 0;
        m_removeFrameButton->setEnabled(hasFrames);
        m_playButton->setEnabled(hasFrames);
    });
}

void spriteEditorView::onPenClicked()
{
    m_activeTool = m_penTool;
    //m_controller->setActiveTool(m_activeTool);
    m_penButton->setChecked(true);
    m_eraserButton->setChecked(false);
}

void spriteEditorView::onEraserClicked()
{
    m_activeTool = m_eraserTool;
    //m_controller->setActiveTool(m_activeTool);
    m_eraserButton->setChecked(true);
    m_penButton->setChecked(false);
}

void spriteEditorView::onAddFrameClicked()
{
    m_model->addFrame();
}

void spriteEditorView::onRemoveFrameClicked()
{
    if (m_model->frameCount() > 0) {
        m_model->removeFrame(m_model->currentFrameIndex());
    }
}

void spriteEditorView::onPlayClicked()
{
    m_playButton->setEnabled(false);
    m_stopButton->setEnabled(true);
    // Start animation - implementation depends on your Animation class
}

void spriteEditorView::onStopClicked()
{
    m_playButton->setEnabled(true);
    m_stopButton->setEnabled(false);
    // Stop animation - implementation depends on your Animation class
}

