# Sprite Editor 

## Overview

  The Sprite Editor is a tool for creating and animating pixelated sprites. From simple graphics tools to animation previews, it is a great tool for 2D game development or pixel art.
  - Draw pixels on canvas with tools
  - Add or delete frames to make animation.
  - Save and load the work as a .ssp file.
  
## Features 
  - **Pen tool:** Click on any pixel to draw on canvas.  
  - **Eraser Tool:** Erase pixels.  
  - **Add and edit frames:** add multiple frames to create an animation. 
  - **Animation Preview:** Set the frame and push the play button to preview the animation
  - **Save and Load:** Save and reopen the sprite
  - **Canvas Resize:** Change the canvas to the desired pixel size.  
  - **Canvas Clean function:** Reset the current frame.
  - **Canvas Color Pannel:** Allow users to choose between colors.
  - **Fill tool:** Fill the same color area at once. (Extra Features)
  - **Flip Canvas:** Flip the image of the current canvas. (Extra Features)
  - **Redo and Undo:** Revert one action to a previous step. (Extra Features)

## Requirements


## How to run
This program is a QT-based program.
To run the program, install QT and clone this repo as a new project.

## Technical Stack Used
  **Language:** C++
  
  **Framework:** QT Framework

  **QT Components**
  - QWidget for UI components.
  - QPainter for rendering graphics.
  - QImage for sprite manipulation.
  - QTimer for animation control.
  - QUndoStack/QUndoCommand for undo/redo functionality.
  - QFileDialog for file operations.
  - QJsonDocument/QJsonObject for file serialization.

  **Architecture Pattern**
    Model-View-Controller architecture
    - SpriteEditorModel: Manages data and business logic.
    - SpriteEditorView: handles UI and user interaction.
    - SpriteEditorController: Coordinates between model and view.

  **Build System**
  - QMake

  **File Format**
  - Custom .ssp file format for sprite data storage using JSON
      

  
