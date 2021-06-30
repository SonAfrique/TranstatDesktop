/****************************************************************************
** Meta object code from reading C++ file 'addcounter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../addcounter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'addcounter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AddCounter_t {
    QByteArrayData data[7];
    char stringdata0[124];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AddCounter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AddCounter_t qt_meta_stringdata_AddCounter = {
    {
QT_MOC_LITERAL(0, 0, 10), // "AddCounter"
QT_MOC_LITERAL(1, 11, 32), // "send_counter_addition_successful"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 4), // "int&"
QT_MOC_LITERAL(4, 50, 31), // "send_counter_addition_cancelled"
QT_MOC_LITERAL(5, 82, 19), // "on_btn_save_clicked"
QT_MOC_LITERAL(6, 102, 21) // "on_btn_cancel_clicked"

    },
    "AddCounter\0send_counter_addition_successful\0"
    "\0int&\0send_counter_addition_cancelled\0"
    "on_btn_save_clicked\0on_btn_cancel_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AddCounter[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    0,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   38,    2, 0x08 /* Private */,
       6,    0,   39,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AddCounter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AddCounter *_t = static_cast<AddCounter *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send_counter_addition_successful((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->send_counter_addition_cancelled(); break;
        case 2: _t->on_btn_save_clicked(); break;
        case 3: _t->on_btn_cancel_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (AddCounter::*_t)(int & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AddCounter::send_counter_addition_successful)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (AddCounter::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AddCounter::send_counter_addition_cancelled)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject AddCounter::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AddCounter.data,
      qt_meta_data_AddCounter,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AddCounter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AddCounter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AddCounter.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int AddCounter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void AddCounter::send_counter_addition_successful(int & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AddCounter::send_counter_addition_cancelled()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
