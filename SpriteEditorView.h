#ifndef SPRITEEDITORVIEW_H
#define SPRITEEDITORVIEW_H

/**
 * @file spriteeditorview.h
 * @brief Declares the SpriteEditorView class, the main GUI controller for the sprite editor.
 *
 * SpriteEditorView manages user interaction with the editor window, including canvas drawing,
 * tool selection, and real-time sprite updates. It serves as the connection between UI components
 * and underlying pixel editing logic.
 *
 * @author Jason chang
 */

#include <QMainWindow>
#include <QVBoxLayout>
#include "tools.h"

namespace Ui {
class SpriteEditorView;
}

class Canvas;

/**
 * @class SpriteEditorView
 * @brief Main window class for the sprite editor GUI.
 */
class SpriteEditorView : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Constructs the SpriteEditorView.
     * @param parent The parent widget (default is nullptr).
     */
    explicit SpriteEditorView(QWidget* parent = nullptr);

    /**
     * @brief Destructor for SpriteEditorView.
     */
    ~SpriteEditorView();

private slots:
    /**
     * @brief Handles mouse press events on the canvas.
     * @param pos Position of the mouse press.
     */
    void handleMousePressed(const QPoint& pos);

    /**
     * @brief Handles mouse drag events on the canvas.
     * @param pos Position of the mouse drag.
     */
    void handleMouseDragged(const QPoint& pos);

    /**
     * @brief Handles mouse release events on the canvas.
     * @param pos Position of the mouse release.
     */
    void handleMouseReleased(const QPoint& pos);

    // Tool selection slots
    void onPenSelected();
    void onEraserSelected();
    void onFillSelected();

private:
    Ui::SpriteEditorView* ui;
    Canvas* canvas;

    // Currently selected tool (default: Pen)
    Tools::ToolType currentTool = Tools::ToolType::Pen;

    // Currently selected color (default: Black)
    Tools::ColorType currentColor = Tools::ColorType::Black;

    // Frame currently being edited
    QImage currentFrame;

    /**
     * @brief Updates the canvas display based on the current frame image.
     */
    void updateCanvasDisplay();

    /**
     * @brief Updates the tool button UI to reflect the selected tool.
     */
    void updateToolButtonStates();
};

#endif // SPRITEEDITORVIEW_H
