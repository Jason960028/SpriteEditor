/****************************************************************************
** Meta object code from reading C++ file 'SpriteEditorController.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../SpriteEditorController.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SpriteEditorController.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN22SpriteEditorControllerE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN22SpriteEditorControllerE = QtMocHelpers::stringData(
    "SpriteEditorController",
    "frameListChanged",
    "",
    "size",
    "animationStateChanged",
    "playing",
    "toolSelectSignal",
    "Tools::ToolType&",
    "tool",
    "currentFrameChanged",
    "handlePlayPressed",
    "handleStopPressed",
    "onPenClicked",
    "onEraserClicked",
    "onFillingClicked",
    "addFrame",
    "removeCurrentFrame",
    "handleFrameSelected",
    "index",
    "moveFrameUp",
    "moveFrameDown"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN22SpriteEditorControllerE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   98,    2, 0x06,    1 /* Public */,
       4,    1,  101,    2, 0x06,    3 /* Public */,
       6,    1,  104,    2, 0x06,    5 /* Public */,
       9,    0,  107,    2, 0x06,    7 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      10,    0,  108,    2, 0x0a,    8 /* Public */,
      11,    0,  109,    2, 0x0a,    9 /* Public */,
      12,    0,  110,    2, 0x0a,   10 /* Public */,
      13,    0,  111,    2, 0x0a,   11 /* Public */,
      14,    0,  112,    2, 0x0a,   12 /* Public */,
      15,    0,  113,    2, 0x0a,   13 /* Public */,
      16,    0,  114,    2, 0x0a,   14 /* Public */,
      17,    1,  115,    2, 0x0a,   15 /* Public */,
      19,    1,  118,    2, 0x0a,   17 /* Public */,
      20,    1,  121,    2, 0x0a,   19 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::Int,   18,

       0        // eod
};

Q_CONSTINIT const QMetaObject SpriteEditorController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ZN22SpriteEditorControllerE.offsetsAndSizes,
    qt_meta_data_ZN22SpriteEditorControllerE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN22SpriteEditorControllerE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<SpriteEditorController, std::true_type>,
        // method 'frameListChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'animationStateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'toolSelectSignal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Tools::ToolType &, std::false_type>,
        // method 'currentFrameChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handlePlayPressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleStopPressed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onPenClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onEraserClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onFillingClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addFrame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'removeCurrentFrame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleFrameSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'moveFrameUp'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'moveFrameDown'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void SpriteEditorController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<SpriteEditorController *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->frameListChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->animationStateChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->toolSelectSignal((*reinterpret_cast< std::add_pointer_t<Tools::ToolType&>>(_a[1]))); break;
        case 3: _t->currentFrameChanged(); break;
        case 4: _t->handlePlayPressed(); break;
        case 5: _t->handleStopPressed(); break;
        case 6: _t->onPenClicked(); break;
        case 7: _t->onEraserClicked(); break;
        case 8: _t->onFillingClicked(); break;
        case 9: _t->addFrame(); break;
        case 10: _t->removeCurrentFrame(); break;
        case 11: _t->handleFrameSelected((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->moveFrameUp((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 13: _t->moveFrameDown((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _q_method_type = void (SpriteEditorController::*)(int );
            if (_q_method_type _q_method = &SpriteEditorController::frameListChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _q_method_type = void (SpriteEditorController::*)(bool );
            if (_q_method_type _q_method = &SpriteEditorController::animationStateChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _q_method_type = void (SpriteEditorController::*)(Tools::ToolType & );
            if (_q_method_type _q_method = &SpriteEditorController::toolSelectSignal; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _q_method_type = void (SpriteEditorController::*)();
            if (_q_method_type _q_method = &SpriteEditorController::currentFrameChanged; *reinterpret_cast<_q_method_type *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *SpriteEditorController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SpriteEditorController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN22SpriteEditorControllerE.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SpriteEditorController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void SpriteEditorController::frameListChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SpriteEditorController::animationStateChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SpriteEditorController::toolSelectSignal(Tools::ToolType & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SpriteEditorController::currentFrameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
