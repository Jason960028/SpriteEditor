#include "spriteEditorView.h"
#include <QToolBar>
#include <QToolButton>
#include <QButtonGroup>
#include <QMessageBox>
#include <QPixmap>
#include <QDebug>
#include "SpriteEditorModel.h"
#include "ui_SpriteEditorView.h"
#include "canvas.h"
#include <QVBoxLayout>
#include "Animation.h"

SpriteEditorView::SpriteEditorView(SpriteEditorModel* model,
                                   SpriteEditorController* m_controller,
                                   QWidget* parent)
    : QMainWindow(parent),
    ui(new Ui::SpriteEditorView),
    m_model(model),
    m_controller(m_controller),
    m_currentTool(Tools::ToolType::Pen),
    m_currentFrame(m_model->getCurrentFrame()),
    m_currentColor(m_model->getCurrentColor())
{
    ui->setupUi(this);

    m_penButton = findChild<QToolButton*>("Pen");
    m_eraserButton = findChild<QToolButton*>("Eraser");
    m_addFrameButton = ui->AddFrame;
    m_deleteFrameButton = ui->DeleteFrame;

    //Load and save
    m_loadButton = ui->loadButton;
    m_saveButton = ui->saveButton;

    m_canvas = new Canvas(this, m_model);
    setupUI();
    m_frameList = ui->frameListWidget;
    connectSignals();

    QVBoxLayout* canvasLayout = new QVBoxLayout(ui->Canvas);
    canvasLayout->setContentsMargins(0, 0, 0, 0);
    canvasLayout->addWidget(m_canvas);

    m_canvas->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    int canvasWidth = m_canvas->getCanvasWidth();
    int canvasHeight = m_canvas->getCanvasHeight();
    int pixelScale = 10;
    m_canvas->setFixedSize(canvasWidth * pixelScale, canvasHeight * pixelScale);

    m_canvas->updateCanvas(m_currentFrame);
    updateFrameList(m_model->getCurrentIndex());

    // Connect the animation widget to the Preview area
    m_animation = new Animation(ui->Preview);
    QVBoxLayout* previewLayout = new QVBoxLayout(ui->Preview);
    previewLayout->setContentsMargins(0, 0, 0, 0);
    previewLayout->addWidget(m_animation);
    m_animation->show();
    m_animation->raise(); // Ensure it appears on top

    // Add existing frames to animation preview initially
    for (int i = 0; i < m_model->getFramesListSize(); ++i) {
        m_animation->addFrame(m_model->getFrame(i));
    }
}

SpriteEditorView::~SpriteEditorView()
{
    delete ui;
}

void SpriteEditorView::setupUI() {}

void SpriteEditorView::setupTools() {
    m_currentTool = m_model->getCurrentTool();
}

void SpriteEditorView::connectSignals()
{
    connect(m_penButton, &QToolButton::clicked, m_controller, &SpriteEditorController::onPenClicked);
    connect(m_eraserButton, &QToolButton::clicked, m_controller, &SpriteEditorController::onEraserClicked);
    connect(ui->moveUpFrameButton, &QToolButton::clicked, this, &SpriteEditorView::onMoveUpClicked);
    connect(ui->moveDownFrameButton, &QToolButton::clicked, this, &SpriteEditorView::onMoveDownClicked);
    connect(m_controller, &SpriteEditorController::currentFrameChanged, this, &SpriteEditorView::handleFrameChanged);
    connect(m_addFrameButton, &QToolButton::clicked, m_controller, &SpriteEditorController::addFrame);
    connect(m_deleteFrameButton, &QToolButton::clicked, m_controller, &SpriteEditorController::removeCurrentFrame);
    connect(m_controller, &SpriteEditorController::frameListChanged, this, &SpriteEditorView::updateFrameList);
    connect(m_controller, &SpriteEditorController::toolSelectSignal, this, &SpriteEditorView::updateToolButtonStates);
    connect(this, &SpriteEditorView::addFrameRequested, m_controller, &SpriteEditorController::addFrame);
    connect(this, &SpriteEditorView::deleteFrameRequested, m_controller, &SpriteEditorController::removeCurrentFrame);
    connect(this, &SpriteEditorView::moveFrameUpRequested, m_controller, &SpriteEditorController::moveFrameUp);
    connect(this, &SpriteEditorView::moveFrameDownRequested, m_controller, &SpriteEditorController::moveFrameDown);
    connect(this, &SpriteEditorView::frameSelected, m_controller, &SpriteEditorController::handleFrameSelected);
    connect(m_frameList, &QListWidget::currentRowChanged, this, &SpriteEditorView::onFrameSelectionChanged);
    connect(m_canvas, &Canvas::mousePressed, this, &SpriteEditorView::handleMousePressed);
    connect(m_canvas, &Canvas::mouseDragged, this, &SpriteEditorView::handleMouseDragged);
    connect(m_canvas, &Canvas::mouseReleased, this, &SpriteEditorView::handleMouseReleased);

    // Connect the Play button to the slot that starts the animation
    connect(ui->Play, &QPushButton::clicked, this, &SpriteEditorView::onPlayButtonClicked);

    // Connect the Stop button to the slot that stops the animation
    connect(ui->Stop, &QPushButton::clicked, this, &SpriteEditorView::onStopButtonClicked);

    // Connect the FPS slider to update the animation frame delay dynamically
    connect(ui->FPS, &QSlider::valueChanged, this, [this](int value) {
        if (value > 0)
            m_animation->setFrameDelay(1000 / value);  // Calculate delay in milliseconds from FPS
    });

    // Connect save and load
    connect(m_loadButton, &QPushButton::clicked, this, &SpriteEditorView::onLoadButtonClicked);
    connect(m_saveButton, &QPushButton::clicked, this, &SpriteEditorView::onSaveButtonClicked);

}

void SpriteEditorView::updateFrameList(int currentIndex)
{
    ui->frameListWidget->blockSignals(true);
    ui->frameListWidget->clear();
    for (int i = 0; i < m_model->getFramesListSize(); ++i) {
        QListWidgetItem *item = new QListWidgetItem(QString("Frame %1").arg(i + 1), ui->frameListWidget);
        item->setIcon(QIcon(":/icons/frame.png"));
    }
    ui->frameListWidget->setCurrentRow(currentIndex);
    updateCanvasDisplay();
    ui->frameListWidget->blockSignals(false);

}

// Slot to update the preview when Animation emits frameChanged signal
void SpriteEditorView::updatePreviewFrame(const QImage &frame) {
    if (m_animation) {
        m_animation->addFrame(frame);
        m_animation->update();
    }
}

// Slot called when the Play button is clicked
void SpriteEditorView::onPlayButtonClicked() {
    if (m_animation) {
        m_animation->clearFrames();  // Clear any previously loaded frames

        // Load all frames from the model into the animation
        for (int i = 0; i < m_model->getFramesListSize(); ++i) {
            m_animation->addFrame(m_model->getFrame(i));
        }

        // Start the animation playback
        m_animation->play();
    }
}

// Slot called when the Stop button is clicked
void SpriteEditorView::onStopButtonClicked() {
    if (m_animation)
        m_animation->stop();  // Stop the animation playback
}

void SpriteEditorView::onAddFrameClicked() {
    emit addFrameRequested();
}

void SpriteEditorView::onDeleteFrameClicked() {
    int index = m_model->getCurrentIndex();
    if (index >= 0) {
        emit deleteFrameRequested(index);
    }
    updateCanvasDisplay();
}

void SpriteEditorView::onMoveUpClicked() {
    int index = m_model->getCurrentIndex();
    if (index > 0) {
        emit moveFrameUpRequested(index);
        ui->frameListWidget->setCurrentRow(index - 1);
    }
}

void SpriteEditorView::onMoveDownClicked() {
    int index = m_model->getCurrentIndex();
    if (index >= 0 && index < ui->frameListWidget->count() - 1) {
        emit moveFrameDownRequested(index);
        ui->frameListWidget->setCurrentRow(index + 1);
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
    ui->Pen->setChecked(false);
    ui->Eraser->setChecked(false);
    ui->Fill->setChecked(false);
    m_currentTool = m_model->getCurrentTool();

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

void SpriteEditorView::onLoadButtonClicked(){
    emit loadClicked();

    // Sets the current frame to the first one and updates the GUI
    QVector<QImage> m_frames = m_model->getFrames();
    if (!m_frames.isEmpty()) {
        m_currentFrame = m_frames[0];  // Set the first frame
        updateFrameList(0);            // Update the frame list
        updatePreviewFrame(m_currentFrame);
        updateCanvasDisplay();         // Update the canvas with the first frame

    }
}

void SpriteEditorView::onSaveButtonClicked(){
    emit saveClicked();
}
