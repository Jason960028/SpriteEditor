#include "SpriteEditorControl.h"
#include "SpriteEditorModel.h"
#include "SpriteEditorView.h"
#include <QFileDialog>
#include <QDebug>

spriteEditorController::spriteEditorController(spriteEditorModel* model, QObject* parent, QWidget* parentWidget)
    : QObject(parent),
    m_model(model),
    m_parentWidget(parentWidget)
{
    // Connect Load and Save signal from view to slots here
    SpriteEditorView* view = qobject_cast<SpriteEditorView*>(parentWidget);  // Cast the parentWidget to spriteEditorView
    if (!view) {
        qWarning() << "Parent widget is not of type SpriteEditorView!";
    }

    if (view) {
        connect(view, &SpriteEditorView::loadClicked, this, &spriteEditorController::onLoadClicked);
        connect(view, &SpriteEditorView::saveClicked, this, &spriteEditorController::onSaveClicked);
    }
}



void spriteEditorController::onLoadClicked() {
    QString fileName = QFileDialog::getOpenFileName(
        m_parentWidget,  // the QWidget* view passed in
        tr("Open SSP File"),
        "",
        tr("SSP Files (*.ssp)")
        );

    if (!fileName.isEmpty()) {
        // Call load function that is inside the model
        m_model->loadSprite(fileName);
    }
}

void spriteEditorController::onSaveClicked(){

    QString fileName = QFileDialog::getSaveFileName(
        m_parentWidget,
        tr("Save File"),
        "", // Optional default filename, e.g., "untitled.ssp"
        tr("Spreadsheet Files (*.ssp)")
        );

    if (!fileName.isEmpty()) {
        m_model->saveSprite(fileName);
    }
}
