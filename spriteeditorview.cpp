#include "spriteeditorview.h"
#include "ui_spriteeditorview.h"

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
