#ifndef SPRITEEDITORVIEW_H
#define SPRITEEDITORVIEW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {

    class SpriteEditorView;

}

QT_END_NAMESPACE

class SpriteEditorView : public QMainWindow
{
    Q_OBJECT

    public:
        SpriteEditorView(QWidget *parent = nullptr);
        ~SpriteEditorView();

    private:
        Ui::SpriteEditorView *ui;
};

#endif // SPRITEEDITORVIEW_H
