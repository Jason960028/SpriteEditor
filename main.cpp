#include "spriteEditorView.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SpriteEditorView w;
    w.show();
    return a.exec();
}
