#include "SpriteEditorView.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SpriteEditorModel model;
    Canvas canvas;
    SpriteEditorController controller(&model, &canvas);
    SpriteEditorView view(&model, &controller);
    controller.setView(&view);

    // Initialize with default project (32x32)
    //model.createNewProject(32, 32);

    // Show the main window
    view.show();
    return a.exec();
}
