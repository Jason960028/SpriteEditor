#include <QApplication>
#include "spriteEditorView.h"
#include "SpriteEditorControl.h"
#include "spriteEditorModel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create the model
    spriteEditorModel model;

    // Create the view (Note: pass a nullptr for parentWidget since we won't be passing the view to itself)
    SpriteEditorView w(nullptr, &model);

    // Create the controller and pass the model to it
    spriteEditorController controller(&model, nullptr, &w);

    // Connect the view and controller
    // The view emits signals (like loadClicked, saveClicked), which the controller listens to and acts on
    QObject::connect(&w, &SpriteEditorView::loadClicked, &controller, &spriteEditorController::onLoadClicked);
    QObject::connect(&w, &SpriteEditorView::saveClicked, &controller, &spriteEditorController::onSaveClicked);

    // Show the view
    w.show();

    return a.exec();
}

