/****************************************************************************
** Meta object code from reading C++ file 'drawcounter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../drawcounter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'drawcounter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DrawCounter_t {
    QByteArrayData data[10];
    char stringdata0[148];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DrawCounter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DrawCounter_t qt_meta_stringdata_DrawCounter = {
    {
QT_MOC_LITERAL(0, 0, 11), // "DrawCounter"
QT_MOC_LITERAL(1, 12, 26), // "send_drawing_task_complete"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 4), // "int&"
QT_MOC_LITERAL(4, 45, 27), // "send_drawing_task_cancelled"
QT_MOC_LITERAL(5, 73, 12), // "mouseHandler"
QT_MOC_LITERAL(6, 86, 12), // "QMouseEvent*"
QT_MOC_LITERAL(7, 99, 5), // "event"
QT_MOC_LITERAL(8, 105, 20), // "on_btn_apply_clicked"
QT_MOC_LITERAL(9, 126, 21) // "on_btn_cancel_clicked"

    },
    "DrawCounter\0send_drawing_task_complete\0"
    "\0int&\0send_drawing_task_cancelled\0"
    "mouseHandler\0QMouseEvent*\0event\0"
    "on_btn_apply_clicked\0on_btn_cancel_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DrawCounter[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    0,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   43,    2, 0x08 /* Private */,
       8,    0,   46,    2, 0x08 /* Private */,
       9,    0,   47,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DrawCounter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DrawCounter *_t = static_cast<DrawCounter *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send_drawing_task_complete((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->send_drawing_task_cancelled(); break;
        case 2: _t->mouseHandler((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 3: _t->on_btn_apply_clicked(); break;
        case 4: _t->on_btn_cancel_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (DrawCounter::*_t)(int & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DrawCounter::send_drawing_task_complete)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DrawCounter::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DrawCounter::send_drawing_task_cancelled)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject DrawCounter::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DrawCounter.data,
      qt_meta_data_DrawCounter,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DrawCounter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DrawCounter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DrawCounter.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int DrawCounter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void DrawCounter::send_drawing_task_complete(int & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DrawCounter::send_drawing_task_cancelled()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
