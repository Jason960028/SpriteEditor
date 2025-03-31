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
#include "RedoUndo.h"

SpriteEditorView::SpriteEditorView(SpriteEditorModel* model,
                                   SpriteEditorController* m_controller,
                                   QWidget* parent)
    : QMainWindow(parent),
    ui(new Ui::SpriteEditorView),
    m_model(model),
    m_controller(m_controller),
    m_currentTool(Tools::ToolType::Pen),
    m_currentFrame(m_model->getCurrentFrame()),
    m_currentColor(m_model->getCurrentColor()),
    m_currentUndoStack(m_model->currentUndoStack())
{
    ui->setupUi(this);

    setupColorPalette();
    setupButtonIcons();
    applyTheme();

    m_penButton = findChild<QToolButton*>("Pen");
    m_eraserButton = findChild<QToolButton*>("Eraser");
    m_fillingButton = findChild<QToolButton*>("Fill");
    m_flipButton = findChild<QToolButton*>("Flip");
    m_addFrameButton = ui->AddFrame;
    m_deleteFrameButton = ui->DeleteFrame;

    //Load and save
    m_loadButton = ui->loadButton;
    m_saveButton = ui->saveButton;

    //Clean
    m_cleanButton = ui->CleanButton;

    // Undo/Redo button
    undoAction = m_model->currentUndoStack()->createUndoAction(this, tr("Undo"));
    redoAction = m_model->currentUndoStack()->createRedoAction(this, tr("Redo"));

    // Set shortcuts
    undoAction->setShortcut(QKeySequence::Undo);
    redoAction->setShortcut(QKeySequence::Redo);

    ui->undoButton->setEnabled(m_model->currentUndoStack()->canUndo());
    ui->redoButton->setEnabled(m_model->currentUndoStack()->canRedo());

    // Logic for currently selected tool visual indicator.
    ui->Pen->setCheckable(true);
    ui->Eraser->setCheckable(true);
    ui->Fill->setCheckable(true);

    // Set up FPS slider and spinbox
    ui->FPSBox->setRange(1, 60);  // Set reasonable range for FPS (1-)
    ui->FPS->setRange(1, 60);     // Match the slider range
    ui->FPSBox->setValue(10);     // Default to 10 FPS
    ui->FPS->setValue(10);        // Set matching default for slider



    // Initial condition, pen selected
    ui->Pen->setChecked(true);

    ui->CanvasFrame->setStyleSheet("QFrame { border: none; }");


    // Canvas setup
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
    connect(m_flipButton, &QToolButton::clicked, m_controller, &SpriteEditorController::onFlipHorizontalClicked);
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

    connect(ui->FPS, &QSlider::valueChanged, ui->FPSBox, &QSpinBox::setValue);
    connect(ui->FPSBox, &QSpinBox::valueChanged, ui->FPS, &QSlider::setValue);
    // Connect the FPS slider to update the animation frame delay dynamically
    connect(ui->FPS, &QSlider::valueChanged, this, [this](int value) {
        if (value > 0)
            m_animation->setFrameDelay(1000 / value);  // Calculate delay in milliseconds from FPS
    });

    // Connect save and load
    connect(m_loadButton, &QPushButton::clicked, this, &SpriteEditorView::onLoadButtonClicked);
    connect(m_saveButton, &QPushButton::clicked, this, &SpriteEditorView::onSaveButtonClicked);
    connect(ui->ResizeButton, &QPushButton::clicked, this, &SpriteEditorView::onResizeClicked);

    // Clean button connection
    connect(m_cleanButton, &QPushButton::clicked, m_controller, &SpriteEditorController::onCleanButtonClicked);


    connect(this, &SpriteEditorView::colorSelected, m_controller, &SpriteEditorController::onColorSelected);
    connect(m_model, &SpriteEditorModel::colorChanged, this, &SpriteEditorView::onModelColorChanged);

    //Redo/Undo connections
    connect(ui->undoButton, &QPushButton::clicked, m_model->currentUndoStack(), &QUndoStack::undo);
    connect(ui->redoButton, &QPushButton::clicked, m_model->currentUndoStack(), &QUndoStack::redo);

    connect(m_model->currentUndoStack(), &QUndoStack::canUndoChanged, ui->undoButton, &QPushButton::setEnabled);
    connect(m_model->currentUndoStack(), &QUndoStack::canRedoChanged, ui->redoButton, &QPushButton::setEnabled);

    connect(m_model, &SpriteEditorModel::pixelsChanged, m_canvas, QOverload<>::of(&Canvas::update));
    connect(m_model->currentUndoStack(), &QUndoStack::indexChanged, m_canvas, QOverload<>::of(&Canvas::update));

    connect(m_model, &SpriteEditorModel::undoStackChanged,
            this, &SpriteEditorView::updateUndoRedoConnections);

    updateUndoRedoConnections();

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
    QImage& currentFrame = m_model->getCurrentFrame();
    Tools::ToolResult result = Tools::applyTool(currentFrame, pos, m_currentTool, m_model->getCurrentColor());

    if(m_currentTool == Tools::ToolType::Fill){
        if (!result.positions.isEmpty()) {
            RedoUndoCommand* cmd = new RedoUndoCommand(
                m_model,
                result.positions,
                result.oldColors,
                result.newColor,
                m_model->getCurrentIndex()
                );
            m_model->currentUndoStack()->push(cmd);
            updateCanvasDisplay();
        }
    }else{
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

void SpriteEditorView::updateSelectedColorButton(int colorIndex)
{
    // Uncheck all buttons
    for (QToolButton *btn : m_colorButtons) {
        btn->setChecked(false);
    }

    // Check the selected button
    if (colorIndex >= 0 && colorIndex < m_colorButtons.size()) {
        m_colorButtons[colorIndex]->setChecked(true);
    }

    // Update the current color frame
    if (m_currentColorFrame) {
        // Update the stylesheet with the new color
        QString colorStyle = QString("QFrame { background-color: %1; border: 1px solid black; }")
                                 .arg(m_currentColor.name());
        m_currentColorFrame->setStyleSheet(colorStyle);

        // Also update the palette for backup approach
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

void SpriteEditorView::updateUndoRedoConnections(){
    QUndoStack* stack = m_model->currentUndoStack();

    // Disconnect previous stack's signals
    if (m_currentUndoStack) {
        disconnect(m_currentUndoStack, &QUndoStack::canUndoChanged,
                   ui->undoButton, nullptr);
        disconnect(m_currentUndoStack, &QUndoStack::canRedoChanged,
                   ui->redoButton, nullptr);
        disconnect(ui->undoButton, &QPushButton::clicked,
                   m_currentUndoStack, &QUndoStack::undo);
        disconnect(ui->redoButton, &QPushButton::clicked,
                   m_currentUndoStack, &QUndoStack::redo);
    }

    // Connect new stack's signals
    connect(stack, &QUndoStack::canUndoChanged,
            ui->undoButton, &QPushButton::setEnabled);
    connect(stack, &QUndoStack::canRedoChanged,
            ui->redoButton, &QPushButton::setEnabled);
    connect(ui->undoButton, &QPushButton::clicked,
            stack, &QUndoStack::undo);
    connect(ui->redoButton, &QPushButton::clicked,
            stack, &QUndoStack::redo);

    // Update button states
    ui->undoButton->setEnabled(stack->canUndo());
    ui->redoButton->setEnabled(stack->canRedo());

    m_currentUndoStack = stack;
}

void SpriteEditorView::setupButtonIcons(){
    // Define icon size
    QSize iconSize(24, 24);

    // Create icons from resource files
    // You'll need to add these icons to a resources.qrc file

    // Tools
    ui->Pen->setIcon(QIcon("://pen.png"));     // Image 7
    ui->Pen->setText("");
    ui->Pen->setIconSize(iconSize);
    ui->Pen->setToolTip("Pen Tool");

    ui->Eraser->setIcon(QIcon("://eraser.png"));   // Image 6
    ui->Eraser->setText("");
    ui->Eraser->setIconSize(iconSize);
    ui->Eraser->setToolTip("Eraser Tool");

    ui->Fill->setIcon(QIcon("://fill.png"));   // Image 8
    ui->Fill->setText("");
    ui->Fill->setIconSize(iconSize);
    ui->Fill->setToolTip("Fill Tool");

    // Frame controls
    ui->AddFrame->setIcon(QIcon("://plus.png"));    // Image 5
    ui->AddFrame->setText("");
    ui->AddFrame->setIconSize(iconSize);
    ui->AddFrame->setToolTip("Add Frame");

    ui->DeleteFrame->setIcon(QIcon("://minus.png"));  // Image 4
    ui->DeleteFrame->setText("");
    ui->DeleteFrame->setIconSize(iconSize);
    ui->DeleteFrame->setToolTip("Delete Frame");

    ui->moveUpFrameButton->setIcon(QIcon("://arrowUp.png"));    // Image 3
    ui->moveUpFrameButton->setText("");
    ui->moveUpFrameButton->setIconSize(iconSize);
    ui->moveUpFrameButton->setToolTip("Move Frame Up");

    ui->moveDownFrameButton->setIcon(QIcon("://arrowDown.png"));    // Image 2
    ui->moveDownFrameButton->setText("");
    ui->moveDownFrameButton->setIconSize(iconSize);
    ui->moveDownFrameButton->setToolTip("Move Frame Down");

    // Flip button
    ui->Flip->setIcon(QIcon("://flip.png"));   // (You could use Image 1 for this)
    ui->Flip->setText("");
    ui->Flip->setIconSize(iconSize);
    ui->Flip->setToolTip("Flip Horizontally");
}


void SpriteEditorView::applyTheme() {
    QFont arialFont("Arial", 9);
    QApplication::setFont(arialFont);
    QFont mediumArialFont("Arial", 11);  // Medium size
    QFont largeArialFont("Arial", 15);   // Large size

    // Color definition
    QColor bgDark = QColor(35, 39, 42);         // Dark gray background
    QColor bgMedium = QColor(44, 47, 51);       // Medium gray panels
    QColor bgLight = QColor(54, 57, 63);        // Light gray elements
    QColor accentPink = QColor(255, 115, 179);  // Pink accent for primary actions
    QColor accentCyan = QColor(124, 232, 255);  // Cyan accent for secondary actions
    QColor accentPurple = QColor(177, 158, 248);// Purple accent for highlights
    QColor textLight = QColor(220, 224, 227);   // Light text
    QColor borderDark = QColor(26, 29, 31);     // Dark border

    // Set the application palette
    QPalette palette;
    palette.setColor(QPalette::Window, bgDark);
    palette.setColor(QPalette::WindowText, textLight);
    palette.setColor(QPalette::Base, bgMedium);
    palette.setColor(QPalette::AlternateBase, bgDark);
    palette.setColor(QPalette::Text, textLight);
    palette.setColor(QPalette::Button, bgMedium);
    palette.setColor(QPalette::ButtonText, textLight);
    palette.setColor(QPalette::Highlight, accentPink);
    palette.setColor(QPalette::HighlightedText, QColor(255, 255, 255));
    this->setPalette(palette);

    // Frame styling with glowing accents
    QString mainFrameStyle = QString("QFrame { "
                                     "  background-color: %1; "
                                     "  border: 1px solid %2; "
                                     "  border-radius: 5px; "
                                     "}")
                                 .arg(bgMedium.name(), borderDark.name());

    QString canvasFrameStyle = QString("QFrame { "
                                       "  background-color: %1; "
                                       "  border: 2px solid %2; "
                                       "  border-radius: 5px; "
                                       "}")
                                   .arg(bgDark.name(), bgDark.name());

    QString previewFrameStyle = QString("QFrame { "
                                        "  background-color: %1; "
                                        "  border: 2px solid %2; "
                                        "  border-radius: 5px; "
                                        "}")
                                    .arg(bgMedium.name(), accentCyan.name());

    // Special styling for the color panel frame to make text visible
    QString colorPanelFrameStyle = QString("QFrame { "
                                           "  background-color: %1; "
                                           "  border: 1px solid %2; "
                                           "  border-radius: 5px; "
                                           "}")
                                       .arg(bgMedium.name(), accentPurple.name());


    // Apply frame styles
    ui->MainFrame->setStyleSheet(mainFrameStyle);
    ui->CanvasFrame->setStyleSheet(canvasFrameStyle);
    ui->ColorPanelFram->setStyleSheet(colorPanelFrameStyle);
    ui->FrameList->setStyleSheet(mainFrameStyle);
    ui->PreviewFrame->setStyleSheet(colorPanelFrameStyle);
    ui->Tool->setStyleSheet(colorPanelFrameStyle);
    ui->frame->setStyleSheet(mainFrameStyle);

    // Make color palette title more visible with specific styling
    QList<QLabel*> colorPanelLabels = ui->ColorPanelFram->findChildren<QLabel*>();
    for (QLabel* label : colorPanelLabels) {
        label->setStyleSheet("QLabel { color: rgb(255, 255, 255); font-weight: bold; font-size: 12px; }");
    }

    // Style color buttons specifically for dark theme
    QList<QToolButton*> colorButtons = ui->ColorPanelFram->findChildren<QToolButton*>();
    for (QToolButton* btn : colorButtons) {
        btn->setStyleSheet(
            "QToolButton { "
            "  background-color: rgb(44, 47, 51); "
            "  border: 1px solid rgb(26, 29, 31); "
            "  border-radius: 3px; "
            "} "
            "QToolButton:hover { "
            "  border: 1px solid rgb(124, 232, 255); "
            "} "
            "QToolButton:checked { "
            "  border: 2px solid rgb(255, 115, 179); "
            "  background-color: rgb(54, 57, 63); "
            "}"
            );
    }




    // Tool button styling with neon-like glow effects
    QString toolButtonStyle = QString("QToolButton { "
                                      "  background-color: %1; "
                                      "  border: 1px solid %2; "
                                      "  border-radius: 5px; "
                                      "} "
                                      "QToolButton:hover { "
                                      "  background-color: %3; "
                                      "  border: 1px solid %4; "
                                      "} "
                                      "QToolButton:pressed { "
                                      "  background-color: %5; "
                                      "} "
                                      "QToolButton:checked { "
                                      "  background-color: %1; "
                                      "  border: 2px solid %4; "
                                      "}")
                                  .arg(bgMedium.name(),
                                       borderDark.name(),
                                       bgLight.name(),
                                       accentPink.name(),
                                       bgDark.name());

    // Apply button styles
    ui->Pen->setStyleSheet(toolButtonStyle);
    ui->Eraser->setStyleSheet(toolButtonStyle);
    ui->Fill->setStyleSheet(toolButtonStyle);
    ui->Flip->setStyleSheet(toolButtonStyle);
    ui->AddFrame->setStyleSheet(toolButtonStyle);
    ui->DeleteFrame->setStyleSheet(toolButtonStyle);
    ui->moveUpFrameButton->setStyleSheet(toolButtonStyle);
    ui->moveDownFrameButton->setStyleSheet(toolButtonStyle);
    ui->Play->setStyleSheet(toolButtonStyle);
    ui->Stop->setStyleSheet(toolButtonStyle);


    // Primary action button styling (pink)
    QString pinkButtonStyle = QString("QPushButton { "
                                      "  background-color: %1; "
                                      "  color: rgb(35, 39, 42); "
                                      "  border: none; "
                                      "  border-radius: 5px; "
                                      "  padding: 5px 10px; "
                                      "  font-weight: bold; "
                                      "} "
                                      "QPushButton:hover { "
                                      "  background-color: %2; "
                                      "} "
                                      "QPushButton:pressed { "
                                      "  background-color: %3; "
                                      "}")
                                  .arg(accentPink.name(),
                                       accentPink.lighter(110).name(),
                                       accentPink.darker(110).name());

    // Apply to primary action buttons
    ui->saveButton->setStyleSheet(pinkButtonStyle);
    ui->loadButton->setStyleSheet(pinkButtonStyle);

    // Secondary action button styling (cyan)
    QString cyanButtonStyle = QString("QPushButton { "
                                      "  background-color: %1; "
                                      "  color: rgb(35, 39, 42); "
                                      "  border: none; "
                                      "  border-radius: 5px; "
                                      "  padding: 5px 10px; "
                                      "  font-weight: bold; "
                                      "} "
                                      "QPushButton:hover { "
                                      "  background-color: %2; "
                                      "} "
                                      "QPushButton:pressed { "
                                      "  background-color: %3; "
                                      "}")
                                  .arg(accentCyan.name(),
                                       accentCyan.lighter(110).name(),
                                       accentCyan.darker(110).name());

    // Apply to secondary action buttons
    ui->ResizeButton->setStyleSheet(cyanButtonStyle);


    // Tertiary action button styling (purple)
    QString purpleButtonStyle = QString("QPushButton { "
                                        "  background-color: %1; "
                                        "  color: rgb(35, 39, 42); "
                                        "  border: none; "
                                        "  border-radius: 5px; "
                                        "  padding: 5px 10px; "
                                        "  font-weight: bold; "
                                        "} "
                                        "QPushButton:hover { "
                                        "  background-color: %2; "
                                        "} "
                                        "QPushButton:pressed { "
                                        "  background-color: %3; "
                                        "}")
                                    .arg(accentPurple.name(),
                                         accentPurple.lighter(110).name(),
                                         accentPurple.darker(110).name());

    ui->CleanButton->setStyleSheet(purpleButtonStyle);
    ui->undoButton->setStyleSheet(purpleButtonStyle);
    ui->redoButton->setStyleSheet(purpleButtonStyle);

    // Style list widget with dark theme and glowing selection
    ui->frameListWidget->setStyleSheet(
        QString("QListWidget { "
                "  background-color: %1; "
                "  border: 1px solid %2; "
                "  border-radius: 5px; "
                "  color: %3; "
                "} "
                "QListWidget::item { "
                "  padding: 6px; "
                "  border-radius: 3px; "
                "  margin: 2px; "
                "} "
                "QListWidget::item:selected { "
                "  background-color: %4; "
                "  color: rgb(35, 39, 42); "
                "} "
                "QListWidget::item:hover:!selected { "
                "  background-color: %5; "
                "}")
            .arg(bgMedium.name(), borderDark.name(),
                 textLight.name(), accentPink.name(), bgLight.name())
        );

    // Style spinboxes with dark theme
    QString spinBoxStyle = QString(
                               "QSpinBox { "
                               "  background-color: %1; "
                               "  color: %3; "
                               "  border: 1px solid %2; "
                               "  border-radius: 5px; "
                               "  padding: 3px; "
                               "}")
                               .arg(bgMedium.name(),
                                    borderDark.name(),
                                    textLight.name());

    ui->SizeBox->setStyleSheet(spinBoxStyle);
    ui->FPSBox->setStyleSheet(spinBoxStyle);
    ui->FPSFrame->setStyleSheet("QFrame { border: none; }");


    // Style sliders with glowing effect
    QString sliderStyle = QString("QSlider::groove:horizontal { "
                                  "  height: 6px; "
                                  "  background: %1; "
                                  "  border-radius: 3px; "
                                  "} "
                                  "QSlider::handle:horizontal { "
                                  "  background: %2; "
                                  "  border: none; "
                                  "  width: 16px; "
                                  "  height: 16px; "
                                  "  margin: -5px 0; "
                                  "  border-radius: 8px; "
                                  "}")
                              .arg(bgLight.name(), accentCyan.name());

    ui->SizeLabel->setFont(largeArialFont);
    ui->FPS->setStyleSheet(sliderStyle);


    if (QLabel* fpsLabel = ui->FPSFrame->findChild<QLabel*>()) {
        fpsLabel->setFont(largeArialFont);
    }

    // For the confirm button
    if (ui->ResizeButton) ui->ResizeButton->setFont(mediumArialFont);


    // Make labels stand out with bright text
    QList<QLabel*> labels = findChildren<QLabel*>();
    for (QLabel* label : labels) {

        label->setStyleSheet("QLabel { color: rgb(255, 255, 255); font-weight: bold; border: none}");
    }
}


