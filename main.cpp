#include "SpriteEditorView.h"
#include "SpriteEditorModel.h"
#include "SpriteEditorControl.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create model first (owns data)
    SpriteEditorModel* model = new SpriteEditorModel();

    // Create controller with model reference
    SpriteEditorController* controller = new SpriteEditorController(model);

    // Create view with model and controller references
    SpriteEditorView* view = new SpriteEditorView(model, controller);

    // Connect view's destruction to application quit to ensure proper cleanup
    QObject::connect(view, &QObject::destroyed, &a, &QApplication::quit);

    // Show the main window
    view->show();

    qDebug() << "Sprite Editor started successfully";

    // Run the application
    int result = a.exec();

    // Clean up resources (view will delete itself when closed)
    delete model;
    delete controller;

    return result;
}
