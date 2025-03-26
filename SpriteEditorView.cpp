#include "SpriteEditorView.h"
#include "ui_SpriteEditorView.h"

SpriteEditorView::SpriteEditorView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SpriteEditorView)
{
    ui->setupUi(this);
}

SpriteEditorView::~SpriteEditorView()
{
    delete ui;
}
