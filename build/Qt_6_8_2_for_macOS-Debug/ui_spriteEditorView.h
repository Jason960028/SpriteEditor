/********************************************************************************
** Form generated from reading UI file 'SpriteEditorView.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPRITEEDITORVIEW_H
#define UI_SPRITEEDITORVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SpriteEditorView
{
public:
    QWidget *centralwidget;
    QFrame *MainFrame;
    QFrame *ImageSequence;
    QPushButton *Image;
    QFrame *CanvasFrame;
    QWidget *Canvas;
    QFrame *MenuBar;
    QToolButton *Menu;
    QToolButton *Save;
    QToolButton *Load;
    QSlider *PenSize;
    QFrame *line;
    QFrame *ColorPanelFram;
    QFrame *PreviewFrame;
    QFrame *PreviewBox;
    QWidget *Preview;
    QPushButton *PlayButton;
    QSlider *FPS;
    QFrame *Tool;
    QToolButton *Fill;
    QToolButton *Pen;
    QToolButton *Eraser;
    QFrame *Layer;
    QPushButton *addLayer;
    QPushButton *moveUp;
    QPushButton *deleteLayer;
    QPushButton *moveDown;
    QFrame *Layerlist;
    QWidget *LayerContent;
    QMenuBar *menubar;

    void setupUi(QMainWindow *SpriteEditorView)
    {
        if (SpriteEditorView->objectName().isEmpty())
            SpriteEditorView->setObjectName("SpriteEditorView");
        SpriteEditorView->resize(1027, 731);
        centralwidget = new QWidget(SpriteEditorView);
        centralwidget->setObjectName("centralwidget");
        MainFrame = new QFrame(centralwidget);
        MainFrame->setObjectName("MainFrame");
        MainFrame->setGeometry(QRect(140, 30, 461, 521));
        MainFrame->setFrameShape(QFrame::Shape::StyledPanel);
        MainFrame->setFrameShadow(QFrame::Shadow::Raised);
        ImageSequence = new QFrame(MainFrame);
        ImageSequence->setObjectName("ImageSequence");
        ImageSequence->setGeometry(QRect(0, 0, 51, 521));
        ImageSequence->setFrameShape(QFrame::Shape::StyledPanel);
        ImageSequence->setFrameShadow(QFrame::Shadow::Raised);
        Image = new QPushButton(ImageSequence);
        Image->setObjectName("Image");
        Image->setGeometry(QRect(10, 20, 31, 31));
        CanvasFrame = new QFrame(MainFrame);
        CanvasFrame->setObjectName("CanvasFrame");
        CanvasFrame->setGeometry(QRect(99, 9, 341, 491));
        CanvasFrame->setFrameShape(QFrame::Shape::StyledPanel);
        CanvasFrame->setFrameShadow(QFrame::Shadow::Raised);
        Canvas = new QWidget(CanvasFrame);
        Canvas->setObjectName("Canvas");
        Canvas->setGeometry(QRect(-1, -1, 341, 491));
        MenuBar = new QFrame(centralwidget);
        MenuBar->setObjectName("MenuBar");
        MenuBar->setGeometry(QRect(0, 0, 801, 31));
        MenuBar->setFrameShape(QFrame::Shape::StyledPanel);
        MenuBar->setFrameShadow(QFrame::Shadow::Raised);
        Menu = new QToolButton(MenuBar);
        Menu->setObjectName("Menu");
        Menu->setGeometry(QRect(0, 0, 61, 31));
        Save = new QToolButton(MenuBar);
        Save->setObjectName("Save");
        Save->setGeometry(QRect(60, 0, 61, 31));
        Load = new QToolButton(MenuBar);
        Load->setObjectName("Load");
        Load->setGeometry(QRect(120, 0, 61, 31));
        PenSize = new QSlider(centralwidget);
        PenSize->setObjectName("PenSize");
        PenSize->setGeometry(QRect(10, 40, 121, 20));
        PenSize->setOrientation(Qt::Orientation::Horizontal);
        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setGeometry(QRect(0, 60, 141, 16));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        ColorPanelFram = new QFrame(centralwidget);
        ColorPanelFram->setObjectName("ColorPanelFram");
        ColorPanelFram->setGeometry(QRect(0, 370, 141, 211));
        ColorPanelFram->setFrameShape(QFrame::Shape::StyledPanel);
        ColorPanelFram->setFrameShadow(QFrame::Shadow::Raised);
        PreviewFrame = new QFrame(centralwidget);
        PreviewFrame->setObjectName("PreviewFrame");
        PreviewFrame->setGeometry(QRect(600, 30, 201, 231));
        PreviewFrame->setFrameShape(QFrame::Shape::StyledPanel);
        PreviewFrame->setFrameShadow(QFrame::Shadow::Raised);
        PreviewBox = new QFrame(PreviewFrame);
        PreviewBox->setObjectName("PreviewBox");
        PreviewBox->setGeometry(QRect(10, 10, 181, 131));
        PreviewBox->setFrameShape(QFrame::Shape::StyledPanel);
        PreviewBox->setFrameShadow(QFrame::Shadow::Raised);
        Preview = new QWidget(PreviewBox);
        Preview->setObjectName("Preview");
        Preview->setGeometry(QRect(-1, -1, 181, 131));
        PlayButton = new QPushButton(PreviewFrame);
        PlayButton->setObjectName("PlayButton");
        PlayButton->setGeometry(QRect(10, 150, 41, 41));
        FPS = new QSlider(PreviewFrame);
        FPS->setObjectName("FPS");
        FPS->setGeometry(QRect(60, 160, 121, 20));
        FPS->setOrientation(Qt::Orientation::Horizontal);
        Tool = new QFrame(centralwidget);
        Tool->setObjectName("Tool");
        Tool->setGeometry(QRect(10, 80, 121, 161));
        Tool->setFrameShape(QFrame::Shape::StyledPanel);
        Tool->setFrameShadow(QFrame::Shadow::Raised);
        Fill = new QToolButton(Tool);
        Fill->setObjectName("Fill");
        Fill->setGeometry(QRect(0, 50, 61, 51));
        Pen = new QToolButton(Tool);
        Pen->setObjectName("Pen");
        Pen->setGeometry(QRect(0, 0, 61, 51));
        Eraser = new QToolButton(Tool);
        Eraser->setObjectName("Eraser");
        Eraser->setGeometry(QRect(60, 0, 61, 51));
        Layer = new QFrame(centralwidget);
        Layer->setObjectName("Layer");
        Layer->setGeometry(QRect(599, 269, 201, 101));
        Layer->setFrameShape(QFrame::Shape::StyledPanel);
        Layer->setFrameShadow(QFrame::Shadow::Raised);
        addLayer = new QPushButton(Layer);
        addLayer->setObjectName("addLayer");
        addLayer->setGeometry(QRect(10, 10, 31, 31));
        moveUp = new QPushButton(Layer);
        moveUp->setObjectName("moveUp");
        moveUp->setGeometry(QRect(60, 10, 31, 31));
        deleteLayer = new QPushButton(Layer);
        deleteLayer->setObjectName("deleteLayer");
        deleteLayer->setGeometry(QRect(160, 10, 31, 31));
        moveDown = new QPushButton(Layer);
        moveDown->setObjectName("moveDown");
        moveDown->setGeometry(QRect(110, 10, 31, 31));
        Layerlist = new QFrame(Layer);
        Layerlist->setObjectName("Layerlist");
        Layerlist->setGeometry(QRect(9, 60, 181, 31));
        Layerlist->setFrameShape(QFrame::Shape::StyledPanel);
        Layerlist->setFrameShadow(QFrame::Shadow::Raised);
        LayerContent = new QWidget(Layerlist);
        LayerContent->setObjectName("LayerContent");
        LayerContent->setGeometry(QRect(-1, -1, 181, 31));
        SpriteEditorView->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SpriteEditorView);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1027, 43));
        SpriteEditorView->setMenuBar(menubar);

        retranslateUi(SpriteEditorView);

        QMetaObject::connectSlotsByName(SpriteEditorView);
    } // setupUi

    void retranslateUi(QMainWindow *SpriteEditorView)
    {
        SpriteEditorView->setWindowTitle(QCoreApplication::translate("SpriteEditorView", "SpriteEditorView", nullptr));
        Image->setText(QCoreApplication::translate("SpriteEditorView", "Image", nullptr));
        Menu->setText(QCoreApplication::translate("SpriteEditorView", "Menu", nullptr));
        Save->setText(QCoreApplication::translate("SpriteEditorView", "Save", nullptr));
        Load->setText(QCoreApplication::translate("SpriteEditorView", "Load", nullptr));
        PlayButton->setText(QCoreApplication::translate("SpriteEditorView", "Play", nullptr));
        Fill->setText(QCoreApplication::translate("SpriteEditorView", "Filling", nullptr));
        Pen->setText(QCoreApplication::translate("SpriteEditorView", "Pen", nullptr));
        Eraser->setText(QCoreApplication::translate("SpriteEditorView", "Eraser", nullptr));
        addLayer->setText(QCoreApplication::translate("SpriteEditorView", "Add", nullptr));
        moveUp->setText(QCoreApplication::translate("SpriteEditorView", "up", nullptr));
        deleteLayer->setText(QCoreApplication::translate("SpriteEditorView", "delete", nullptr));
        moveDown->setText(QCoreApplication::translate("SpriteEditorView", "down", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SpriteEditorView: public Ui_SpriteEditorView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPRITEEDITORVIEW_H
