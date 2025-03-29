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

    setupColorPalette();

    m_penButton = findChild<QToolButton*>("Pen");
    m_eraserButton = findChild<QToolButton*>("Eraser");
    m_fillingButton = findChild<QToolButton*>("Fill");
    m_addFrameButton = ui->AddFrame;
    m_deleteFrameButton = ui->DeleteFrame;

    //Load and save
    m_loadButton = ui->loadButton;
    m_saveButton = ui->saveButton;

    m_canvas = new Canvas(this, m_model);
    setupUI();
    m_frameList = ui->frameListWidget;
    connectSignals();

    QGridLayout* canvasLayout = new QGridLayout(ui->CanvasFrame);
    canvasLayout->setContentsMargins(0, 0, 0, 0);
    canvasLayout->addWidget(m_canvas, 0, 0, Qt::AlignCenter);

    m_canvas->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    int canvasWidth = m_canvas->getCanvasWidth();
    int canvasHeight = m_canvas->getCanvasHeight();
    int pixelScale = 10;
    m_canvas->setFixedSize(canvasWidth * pixelScale, canvasHeight * pixelScale);

    if (ui->Canvas) {
        ui->Canvas->deleteLater();
    }

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

    m_sizeSpinBox = ui->SizeBox;
    m_sizeSpinBox->setRange(32, 64);
    m_sizeSpinBox->setValue(m_model->getFramesListSize());
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
    connect(m_fillingButton, &QToolButton::clicked, m_controller, &SpriteEditorController::onFillingClicked);
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
    connect(ui->ResizeButton, &QPushButton::clicked, this, &SpriteEditorView::onResizeClicked);

    connect(this, &SpriteEditorView::colorSelected, m_controller, &SpriteEditorController::onColorSelected);
    connect(m_model, &SpriteEditorModel::colorChanged, this, &SpriteEditorView::onModelColorChanged);


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
        Tools::applyTool(m_model->getCurrentFrame(), pos, m_currentTool, m_model->getCurrentColor());
        updateCanvasDisplay();
    }
}

void SpriteEditorView::handleMouseDragged(const QPoint& pos) {
    if (pos.x() >= 0 && pos.y() >= 0) {
        Tools::applyTool(m_model->getCurrentFrame(), pos, m_currentTool, m_model->getCurrentColor());
        updateCanvasDisplay();
    }
}

void SpriteEditorView::handleMouseReleased(const QPoint& pos) {
    if (pos.x() >= 0 && pos.y() >= 0) {
        Tools::applyTool(m_model->getCurrentFrame(), pos, m_currentTool, m_model->getCurrentColor());
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

void SpriteEditorView::onResizeClicked(){
    int newSize = m_sizeSpinBox->value();

    if (newSize != m_model->getFrameSize().width()) {
        applyResize(newSize);
    }
}

void SpriteEditorView::applyResize(int size)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Resize Canvas",
                                  QString("Resizing to %1x%1 will scale all frames. Continue?")
                                      .arg(size),
                                  QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        m_model->resizeAllFrames(size);
        m_canvas->resetCanvasSize();

        // Update the Canvas widget's fixed size based on the new dimensions
        int pixelScale = 10; // Match the initial scale factor
        m_canvas->setFixedSize(size * pixelScale, size * pixelScale);

        updateCanvasDisplay();

        // Update animation preview
        if (m_animation) {
            m_animation->clearFrames();
            for (int i = 0; i < m_model->getFramesListSize(); ++i) {
                m_animation->addFrame(m_model->getFrame(i));
            }
        }
    } else {
        // Reset spin box to current size
        m_sizeSpinBox->setValue(m_model->getFrameSize().width());
    }
}

void SpriteEditorView::setupColorPalette() {
    // Create a grid layout for the color palette
    QGridLayout* colorLayout = new QGridLayout(ui->ColorPanelFram);

    // Set consistent spacing and margins
    colorLayout->setContentsMargins(8, 8, 8, 8);
    colorLayout->setSpacing(6);
    colorLayout->setAlignment(Qt::AlignCenter);



    // Add label
    QLabel* colorLabel = new QLabel("Color Palette", ui->ColorPanelFram);
    colorLabel->setAlignment(Qt::AlignCenter);
    QFont labelFont = colorLabel->font();
    labelFont.setBold(true);
    colorLabel->setFont(labelFont);
    colorLayout->addWidget(colorLabel, 0, 0, 1, 4);

    // Create color buttons for each color in the Tools::ColorType enum
    int row = 1;
    int col = 0;
    const int numColumns = 4;

    // Calculate button size based on panel width
    int frameWidth = ui->ColorPanelFram->width();
    int buttonSize = (frameWidth - 40) / numColumns; // 40 pixels for margins and spacing
    buttonSize = qMin(buttonSize, 36); // Cap size to prevent overly large buttons

    for (int i = 0; i < 16; i++) {
        // Convert from index to ColorType enum value
        Tools::ColorType colorType = static_cast<Tools::ColorType>(i);
        QColor color = Tools::getQColor(colorType);

        QToolButton* colorBtn = new QToolButton(ui->ColorPanelFram);
        colorBtn->setFixedSize(buttonSize, buttonSize);

        // Create a pixmap with the color
        QPixmap pixmap(buttonSize - 4, buttonSize - 4); // Slightly smaller for border
        pixmap.fill(color);

        // Set the pixmap as an icon with proper sizing
        colorBtn->setIcon(QIcon(pixmap));
        colorBtn->setIconSize(pixmap.size());
        colorBtn->setProperty("colorIndex", i);

        // Make it checkable and set style
        colorBtn->setCheckable(true);
        colorBtn->setStyleSheet("QToolButton { border: 1px solid darkgray; } "
                                "QToolButton:checked { border: 2px solid black; background-color: lightgray; }");

        // Connect the button click to color selection
        connect(colorBtn, &QToolButton::clicked, this, [this, i]() {
            onColorSelected(i);
        });

        // Add to layout with proper position
        colorLayout->addWidget(colorBtn, row, col);
        m_colorButtons.append(colorBtn);

        col++;
        if (col >= numColumns) {
            col = 0;
            row++;
        }
    }



    // Add "Current Color" label on its own row, centered and spanning all columns
    QLabel* currentLabel = new QLabel("Current Color", ui->ColorPanelFram);
    currentLabel->setAlignment(Qt::AlignCenter);
    colorLayout->addWidget(currentLabel, row + 1, 0, 1, 4);

    // Create a frame to display the current color in the row below the label
    QFrame* currentColorFrame = new QFrame(ui->ColorPanelFram);
    // Make it wider since it spans all columns
    currentColorFrame->setFixedSize(frameWidth - 20, buttonSize);
    currentColorFrame->setFrameShape(QFrame::Box);
    currentColorFrame->setFrameShadow(QFrame::Sunken);
    currentColorFrame->setAutoFillBackground(true);

    // Set initial color
    QPalette pal = currentColorFrame->palette();
    pal.setColor(QPalette::Window, m_currentColor);
    currentColorFrame->setPalette(pal);

    // Place color frame below the label
    colorLayout->addWidget(currentColorFrame, row + 2, 0, 1, 4);

    // Store the current color frame for updates
    m_currentColorFrame = currentColorFrame;

    // Set equal stretch for all columns to ensure even spacing
    for (int i = 0; i < numColumns; i++) {
        colorLayout->setColumnStretch(i, 1);
    }

    // Initialize by selecting the first color (black)
    updateSelectedColorButton(0);
}

// Note: With this implementation, you can remove the createColorButton method
// since we're creating the buttons directly in the setupColorPalette method

QToolButton* SpriteEditorView::createColorButton(const QColor& color, int index) {
    QToolButton* button = new QToolButton(ui->ColorPanelFram);
    button->setFixedSize(30, 30);

    // Create a pixmap with the color
    QPixmap pixmap(24, 24);
    pixmap.fill(color);

    // Set the pixmap as an icon
    button->setIcon(QIcon(pixmap));
    button->setIconSize(pixmap.size());
    button->setProperty("colorIndex", index);

    // Make it checkable for the selection indicator
    button->setCheckable(true);

    // Connect the button click to color selection
    connect(button, &QToolButton::clicked, this, [this, index]() {
        onColorSelected(index);
    });

    return button;
}

void SpriteEditorView::updateSelectedColorButton(int colorIndex) {
    // Uncheck all buttons
    for (QToolButton* btn : m_colorButtons) {
        btn->setChecked(false);
    }

    // Check the selected button
    if (colorIndex >= 0 && colorIndex < m_colorButtons.size()) {
        m_colorButtons[colorIndex]->setChecked(true);
    }

    // Update the current color frame
    if (m_currentColorFrame) {
        QPalette pal = m_currentColorFrame->palette();
        pal.setColor(QPalette::Window, m_currentColor);
        m_currentColorFrame->setPalette(pal);
    }
}

void SpriteEditorView::onColorSelected(int colorIndex) {
    // Convert from index to ColorType enum value
    Tools::ColorType colorType = static_cast<Tools::ColorType>(colorIndex);
    QColor newColor = Tools::getQColor(colorType);

    // Update internal state
    m_currentColor = newColor;

    // Update the visual indicator
    updateSelectedColorButton(colorIndex);

    // Update the model through the controller
    emit colorSelected(newColor);
}

void SpriteEditorView::onModelColorChanged(const QColor& color) {
    m_currentColor = color;

    // Find the button that matches this color and select it
    for (int i = 0; i < m_colorButtons.size(); i++) {
        Tools::ColorType colorType = static_cast<Tools::ColorType>(i);
        if (Tools::getQColor(colorType) == color) {
            updateSelectedColorButton(i);
            break;
        }
    }
}

