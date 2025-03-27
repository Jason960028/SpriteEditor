/********************************************************************************
** Form generated from reading UI file 'spriteEditorView.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPRITEEDITORVIEW_H
#define UI_SPRITEEDITORVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SpriteEditorView
{
public:
    QAction *actionTool;
    QWidget *centralwidget;
    QFrame *MainFrame;
    QFrame *FrameList;
    QToolButton *AddFrame;
    QPushButton *pushButton;
    QToolButton *DeleteFrame;
    QFrame *CanvasFrame;
    QWidget *Canvas;
    QSlider *PenSize;
    QFrame *line;
    QFrame *ColorPanelFram;
    QFrame *PreviewFrame;
    QFrame *PreviewBox;
    QWidget *Preview;
    QSlider *FPS;
    QToolButton *Play;
    QToolButton *S;
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
    QFrame *frame;
    QPushButton *saveButton;
    QPushButton *loadButton;
    QPushButton *CleanButton;
    QPushButton *redoButton;
    QPushButton *undoButton;

    void setupUi(QMainWindow *SpriteEditorView)
    {
        if (SpriteEditorView->objectName().isEmpty())
            SpriteEditorView->setObjectName("SpriteEditorView");
        SpriteEditorView->resize(800, 600);
        actionTool = new QAction(SpriteEditorView);
        actionTool->setObjectName("actionTool");
        actionTool->setMenuRole(QAction::MenuRole::NoRole);
        centralwidget = new QWidget(SpriteEditorView);
        centralwidget->setObjectName("centralwidget");
        MainFrame = new QFrame(centralwidget);
        MainFrame->setObjectName("MainFrame");
        MainFrame->setGeometry(QRect(140, 30, 461, 521));
        MainFrame->setFrameShape(QFrame::Shape::StyledPanel);
        MainFrame->setFrameShadow(QFrame::Shadow::Raised);
        FrameList = new QFrame(MainFrame);
        FrameList->setObjectName("FrameList");
        FrameList->setGeometry(QRect(0, 0, 51, 521));
        FrameList->setFrameShape(QFrame::Shape::StyledPanel);
        FrameList->setFrameShadow(QFrame::Shadow::Raised);
        AddFrame = new QToolButton(FrameList);
        AddFrame->setObjectName("AddFrame");
        AddFrame->setGeometry(QRect(10, 10, 31, 21));
        pushButton = new QPushButton(FrameList);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 130, 31, 21));
        DeleteFrame = new QToolButton(FrameList);
        DeleteFrame->setObjectName("DeleteFrame");
        DeleteFrame->setGeometry(QRect(10, 40, 31, 21));
        CanvasFrame = new QFrame(MainFrame);
        CanvasFrame->setObjectName("CanvasFrame");
        CanvasFrame->setGeometry(QRect(69, 9, 371, 491));
        CanvasFrame->setFrameShape(QFrame::Shape::StyledPanel);
        CanvasFrame->setFrameShadow(QFrame::Shadow::Raised);
        Canvas = new QWidget(CanvasFrame);
        Canvas->setObjectName("Canvas");
        Canvas->setGeometry(QRect(-1, -1, 371, 491));
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
        FPS = new QSlider(PreviewFrame);
        FPS->setObjectName("FPS");
        FPS->setGeometry(QRect(60, 160, 121, 20));
        FPS->setOrientation(Qt::Orientation::Horizontal);
        Play = new QToolButton(PreviewFrame);
        Play->setObjectName("Play");
        Play->setGeometry(QRect(10, 150, 31, 23));
        S = new QToolButton(PreviewFrame);
        S->setObjectName("S");
        S->setGeometry(QRect(10, 180, 31, 23));
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
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(-1, 0, 801, 21));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        saveButton = new QPushButton(frame);
        saveButton->setObjectName("saveButton");
        saveButton->setGeometry(QRect(0, 0, 71, 21));
        loadButton = new QPushButton(frame);
        loadButton->setObjectName("loadButton");
        loadButton->setGeometry(QRect(70, 0, 71, 21));
        CleanButton = new QPushButton(frame);
        CleanButton->setObjectName("CleanButton");
        CleanButton->setGeometry(QRect(140, 0, 71, 21));
        redoButton = new QPushButton(frame);
        redoButton->setObjectName("redoButton");
        redoButton->setGeometry(QRect(210, 0, 71, 21));
        undoButton = new QPushButton(frame);
        undoButton->setObjectName("undoButton");
        undoButton->setGeometry(QRect(280, 0, 71, 21));
        SpriteEditorView->setCentralWidget(centralwidget);

        retranslateUi(SpriteEditorView);

        QMetaObject::connectSlotsByName(SpriteEditorView);
    } // setupUi

    void retranslateUi(QMainWindow *SpriteEditorView)
    {
        SpriteEditorView->setWindowTitle(QCoreApplication::translate("SpriteEditorView", "SpriteEditorView", nullptr));
        actionTool->setText(QCoreApplication::translate("SpriteEditorView", "Tool", nullptr));
        AddFrame->setText(QCoreApplication::translate("SpriteEditorView", "add", nullptr));
        pushButton->setText(QCoreApplication::translate("SpriteEditorView", "PushButton", nullptr));
        DeleteFrame->setText(QCoreApplication::translate("SpriteEditorView", "delete", nullptr));
        Play->setText(QCoreApplication::translate("SpriteEditorView", "Play", nullptr));
        S->setText(QCoreApplication::translate("SpriteEditorView", "Stop", nullptr));
        Fill->setText(QCoreApplication::translate("SpriteEditorView", "Filling", nullptr));
        Pen->setText(QCoreApplication::translate("SpriteEditorView", "Pen", nullptr));
        Eraser->setText(QCoreApplication::translate("SpriteEditorView", "Eraser", nullptr));
        addLayer->setText(QCoreApplication::translate("SpriteEditorView", "Add", nullptr));
        moveUp->setText(QCoreApplication::translate("SpriteEditorView", "up", nullptr));
        deleteLayer->setText(QCoreApplication::translate("SpriteEditorView", "delete", nullptr));
        moveDown->setText(QCoreApplication::translate("SpriteEditorView", "down", nullptr));
        saveButton->setText(QCoreApplication::translate("SpriteEditorView", "Save", nullptr));
        loadButton->setText(QCoreApplication::translate("SpriteEditorView", "Load", nullptr));
        CleanButton->setText(QCoreApplication::translate("SpriteEditorView", "Clean", nullptr));
        redoButton->setText(QCoreApplication::translate("SpriteEditorView", "Redo", nullptr));
        undoButton->setText(QCoreApplication::translate("SpriteEditorView", "Undo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SpriteEditorView: public Ui_SpriteEditorView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPRITEEDITORVIEW_H
