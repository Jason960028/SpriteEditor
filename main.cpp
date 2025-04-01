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

    // Show the main window
    view.show();
    return a.exec();
}
