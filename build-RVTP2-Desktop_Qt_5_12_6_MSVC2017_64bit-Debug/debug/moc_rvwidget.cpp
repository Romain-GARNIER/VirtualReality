/****************************************************************************
** Meta object code from reading C++ file 'rvwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../RVTP2/rvwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rvwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RVWidget_t {
    QByteArrayData data[13];
    char stringdata0[131];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RVWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RVWidget_t qt_meta_stringdata_RVWidget = {
    {
QT_MOC_LITERAL(0, 0, 8), // "RVWidget"
QT_MOC_LITERAL(1, 9, 6), // "update"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 14), // "startAnimation"
QT_MOC_LITERAL(4, 32, 9), // "changeFov"
QT_MOC_LITERAL(5, 42, 5), // "angle"
QT_MOC_LITERAL(6, 48, 13), // "changeOpacity"
QT_MOC_LITERAL(7, 62, 7), // "opacity"
QT_MOC_LITERAL(8, 70, 15), // "changeWireframe"
QT_MOC_LITERAL(9, 86, 13), // "changeCulling"
QT_MOC_LITERAL(10, 100, 11), // "changeScale"
QT_MOC_LITERAL(11, 112, 16), // "changeSaturation"
QT_MOC_LITERAL(12, 129, 1) // "g"

    },
    "RVWidget\0update\0\0startAnimation\0"
    "changeFov\0angle\0changeOpacity\0opacity\0"
    "changeWireframe\0changeCulling\0changeScale\0"
    "changeSaturation\0g"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RVWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x09 /* Protected */,
       4,    1,   56,    2, 0x09 /* Protected */,
       6,    1,   59,    2, 0x09 /* Protected */,
       8,    1,   62,    2, 0x09 /* Protected */,
       9,    1,   65,    2, 0x09 /* Protected */,
      10,    1,   68,    2, 0x09 /* Protected */,
      11,    1,   71,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,   12,

       0        // eod
};

void RVWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RVWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->update(); break;
        case 1: _t->startAnimation(); break;
        case 2: _t->changeFov((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->changeOpacity((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->changeWireframe((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->changeCulling((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->changeScale((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->changeSaturation((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RVWidget::staticMetaObject = { {
    &QOpenGLWidget::staticMetaObject,
    qt_meta_stringdata_RVWidget.data,
    qt_meta_data_RVWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RVWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RVWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RVWidget.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QOpenGLFunctions"))
        return static_cast< QOpenGLFunctions*>(this);
    return QOpenGLWidget::qt_metacast(_clname);
}

int RVWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE