/****************************************************************************
** Meta object code from reading C++ file 'SpriteEditorView.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../SpriteEditorView.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SpriteEditorView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN16SpriteEditorViewE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN16SpriteEditorViewE = QtMocHelpers::stringData(
    "SpriteEditorView",
    "addFrameRequested",
    "",
    "deleteFrameRequested",
    "index",
    "moveFrameUpRequested",
    "moveFrameDownRequested",
    "frameSelected",
    "handleMousePressed",
    "pos",
    "handleMouseDragged",
    "handleMouseReleased",
    "handleFrameChanged",
    "updateFrameList",
    "currentIndex",
    "onAddFrameClicked",
    "onDeleteFrameClicked",
    "onMoveUpClicked",
    "onMoveDownClicked",
    "onFrameSelectionChanged",
    "updateToolButtonStates",
    "updatePreviewFrame",
    "frame",
    "onPlayButtonClicked",
    "onStopButtonClicked"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN16SpriteEditorViewE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  128,    2, 0x06,    1 /* Public */,
       3,    1,  129,    2, 0x06,    2 /* Public */,
       5,    1,  132,    2, 0x06,    4 /* Public */,
       6,    1,  135,    2, 0x06,    6 /* Public */,
       7,    1,  138,    2, 0x06,    8 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       8,    1,  141,    2, 0x08,   10 /* Private */,
      10,    1,  144,    2, 0x08,   12 /* Private */,
      11,    1,  147,    2, 0x08,   14 /* Private */,
      12,    0,  150,    2, 0x08,   16 /* Private */,
      13,    1,  151,    2, 0x08,   17 /* Private */,
      15,    0,  154,    2, 0x08,   19 /* Private */,
      16,    0,  155,    2, 0x08,   20 /* Private */,
      17,    0,  156,    2, 0x08,   21 /* Private */,
      18,    0,  157,    2, 0x08,   22 /* Private */,
      19,    0,  158,    2, 0x08,   23 /* Private */,
      20,    0,  159,    2, 0x08,   24 /* Private */,
      21,    1,  160,    2, 0x08,   25 /* Private */,
      23,    0,  163,    2, 0x08,   27 /* Private */,
      24,    0,  164,    2, 0x08,   28 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QPoint,    9,
    QMetaType::Void, QMetaType::QPoint,    9,
    QMetaType::Void, QMetaType::QPoint,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,   22,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject SpriteEditorView::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_ZN16SpriteEditorViewE.offsetsAndSizes,
    qt_meta_data_ZN16SpriteEditorViewE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN16SpriteEditorViewE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SpriteEditorView, std::true_type>,
        // method 'addFrameRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'deleteFrameRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'moveFrameUpRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'moveFrameDownRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'frameSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'handleMousePressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPoint &, std::false_type>,
        // method 'handleMouseDragged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPoint &, std::false_type>,
        // method 'handleMouseReleased'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPoint &, std::false_type>,
        // method 'handleFrameChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateFrameList'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onAddFrameClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDeleteFrameClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onMoveUpClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onMoveDownClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onFrameSelectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateToolButtonStates'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updatePreviewFrame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QImage &, std::false_type>,
        // method 'onPlayButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onStopButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void SpriteEditorView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<SpriteEditorView *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->addFrameRequested(); break;
        case 1: _t->deleteFrameRequested((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->moveFrameUpRequested((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->moveFrameDownRequested((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->frameSelected((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->handleMousePressed((*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[1]))); break;
        case 6: _t->handleMouseDragged((*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[1]))); break;
        case 7: _t->handleMouseReleased((*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[1]))); break;
        case 8: _t->handleFrameChanged(); break;
        case 9: _t->updateFrameList((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->onAddFrameClicked(); break;
        case 11: _t->onDeleteFrameClicked(); break;
        case 12: _t->onMoveUpClicked(); break;
        case 13: _t->onMoveDownClicked(); break;
        case 14: _t->onFrameSelectionChanged(); break;
        case 15: _t->updateToolButtonStates(); break;
        case 16: _t->updatePreviewFrame((*reinterpret_cast< std::add_pointer_t<QImage>>(_a[1]))); break;
        case 17: _t->onPlayButtonClicked(); break;
        case 18: _t->onStopButtonClicked(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (SpriteEditorView::*)();
            if (_q_method_type _q_method = &SpriteEditorView::addFrameRequested; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (SpriteEditorView::*)(int );
            if (_q_method_type _q_method = &SpriteEditorView::deleteFrameRequested; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (SpriteEditorView::*)(int );
            if (_q_method_type _q_method = &SpriteEditorView::moveFrameUpRequested; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (SpriteEditorView::*)(int );
            if (_q_method_type _q_method = &SpriteEditorView::moveFrameDownRequested; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _q_method_type = void (SpriteEditorView::*)(int );
            if (_q_method_type _q_method = &SpriteEditorView::frameSelected; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject *SpriteEditorView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SpriteEditorView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN16SpriteEditorViewE.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int SpriteEditorView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void SpriteEditorView::addFrameRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SpriteEditorView::deleteFrameRequested(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SpriteEditorView::moveFrameUpRequested(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SpriteEditorView::moveFrameDownRequested(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SpriteEditorView::frameSelected(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
