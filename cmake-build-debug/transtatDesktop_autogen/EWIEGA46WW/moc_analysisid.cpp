/****************************************************************************
** Meta object code from reading C++ file 'analysisid.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../analysisid.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'analysisid.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AnalysisId_t {
    QByteArrayData data[7];
    char stringdata0[135];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AnalysisId_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AnalysisId_t qt_meta_stringdata_AnalysisId = {
    {
QT_MOC_LITERAL(0, 0, 10), // "AnalysisId"
QT_MOC_LITERAL(1, 11, 35), // "send_analysis_id_added_succes..."
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 8), // "QString&"
QT_MOC_LITERAL(4, 57, 35), // "send_analysis_id_addition_can..."
QT_MOC_LITERAL(5, 93, 19), // "on_btn_save_clicked"
QT_MOC_LITERAL(6, 113, 21) // "on_btn_cancel_clicked"

    },
    "AnalysisId\0send_analysis_id_added_successfully\0"
    "\0QString&\0send_analysis_id_addition_cancelled\0"
    "on_btn_save_clicked\0on_btn_cancel_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AnalysisId[] = {

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

void AnalysisId::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AnalysisId *_t = static_cast<AnalysisId *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send_analysis_id_added_successfully((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->send_analysis_id_addition_cancelled(); break;
        case 2: _t->on_btn_save_clicked(); break;
        case 3: _t->on_btn_cancel_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (AnalysisId::*_t)(QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AnalysisId::send_analysis_id_added_successfully)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (AnalysisId::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AnalysisId::send_analysis_id_addition_cancelled)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject AnalysisId::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AnalysisId.data,
      qt_meta_data_AnalysisId,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AnalysisId::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AnalysisId::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AnalysisId.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int AnalysisId::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void AnalysisId::send_analysis_id_added_successfully(QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AnalysisId::send_analysis_id_addition_cancelled()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
