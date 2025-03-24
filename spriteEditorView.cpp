#include "spriteEditorView.h"
#include "ui_spriteEditorView.h"

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
