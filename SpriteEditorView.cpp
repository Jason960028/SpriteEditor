/**
 * @file SpriteEditorView.cpp
 * @brief Implements the SpriteEditorView class, which serves as the main controller for the sprite editor GUI.
 *
 * This class handles tool selection, mouse interactions with the canvas, and manages the
 * display of the sprite frame being edited.
 *
 * @author Team AJKJ (Arthur Mo, Jason Chang, Dongjoo Lee, Kirra Kotsenburg)
 */

#include "SpriteEditorView.h"
#include "ui_SpriteEditorView.h"
#include "canvas.h"
#include "tools.h"

SpriteEditorView::SpriteEditorView(QWidget* parent)
    : QMainWindow(parent),
    ui(new Ui::SpriteEditorView) {

    ui->setupUi(this);

    // Create Canvas object
    canvas = new Canvas(this);

    // Set up layout for CanvasFrame
    QVBoxLayout* canvasLayout = new QVBoxLayout(ui->Canvas);
    canvasLayout->setContentsMargins(0, 0, 0, 0);
    canvasLayout->addWidget(canvas);

    // Set layout policy to Fixed to maintain exact Canvas size
    canvas->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // Get canvas dimensions through accessors
    int canvasWidth = canvas->getCanvasWidth();
    int canvasHeight = canvas->getCanvasHeight();

    // Adjust size to display the grid with scaling
    int pixelScale = 10;
    canvas->setFixedSize(canvasWidth * pixelScale, canvasHeight * pixelScale);

    // Initialize frame image
    currentFrame = QImage(canvasWidth, canvasHeight, QImage::Format_ARGB32);
    currentFrame.fill(Qt::transparent);

    // Update canvas with initial frame
    canvas->updateCanvas(currentFrame);

    // Connect canvas interaction signals
    connect(canvas, &Canvas::mousePressed, this, &SpriteEditorView::handleMousePressed);
    connect(canvas, &Canvas::mouseDragged, this, &SpriteEditorView::handleMouseDragged);
    connect(canvas, &Canvas::mouseReleased, this, &SpriteEditorView::handleMouseReleased);

    // Connect tool selection buttons
    connect(ui->Pen, &QToolButton::clicked, this, &SpriteEditorView::onPenSelected);
    connect(ui->Eraser, &QToolButton::clicked, this, &SpriteEditorView::onEraserSelected);
    connect(ui->Fill, &QToolButton::clicked, this, &SpriteEditorView::onFillSelected);

    // Set Pen button as default
    ui->Pen->setChecked(true);
}

// Tool selection handlers

void SpriteEditorView::onPenSelected() {
    currentTool = Tools::ToolType::Pen;
    updateToolButtonStates();
}

void SpriteEditorView::onEraserSelected() {
    currentTool = Tools::ToolType::Eraser;
    updateToolButtonStates();
}

void SpriteEditorView::onFillSelected() {
    currentTool = Tools::ToolType::Fill;
    updateToolButtonStates();
}

void SpriteEditorView::updateToolButtonStates() {
    // Uncheck all tool buttons
    ui->Pen->setChecked(false);
    ui->Eraser->setChecked(false);
    ui->Fill->setChecked(false);

    // Check the button for the current tool
    switch (currentTool) {
    case Tools::ToolType::Pen:
        ui->Pen->setChecked(true);
        break;
    case Tools::ToolType::Eraser:
        ui->Eraser->setChecked(true);
        break;
    case Tools::ToolType::Fill:
        ui->Fill->setChecked(true);
        break;
    }
}

// Mouse interaction handlers

void SpriteEditorView::handleMousePressed(const QPoint& pos) {
    if (pos.x() >= 0 && pos.y() >= 0) {
        Tools::applyTool(currentFrame, pos, currentTool, currentColor);
        updateCanvasDisplay();
    }
}

void SpriteEditorView::handleMouseDragged(const QPoint& pos) {
    if (pos.x() >= 0 && pos.y() >= 0) {
        Tools::applyTool(currentFrame, pos, currentTool, currentColor);
        updateCanvasDisplay();
    }
}

void SpriteEditorView::handleMouseReleased(const QPoint& pos) {
    if (pos.x() >= 0 && pos.y() >= 0) {
        Tools::applyTool(currentFrame, pos, currentTool, currentColor);
        updateCanvasDisplay();
    }
}

void SpriteEditorView::updateCanvasDisplay() {
    canvas->updateCanvas(currentFrame);
}

SpriteEditorView::~SpriteEditorView() {
    delete ui;
}
