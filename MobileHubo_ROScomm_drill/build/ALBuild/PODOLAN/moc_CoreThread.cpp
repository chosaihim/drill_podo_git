/****************************************************************************
** Meta object code from reading C++ file 'CoreThread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/ALPrograms/PODOLAN/CoreThread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CoreThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CoreThread_t {
    QByteArrayData data[1];
    char stringdata0[11];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CoreThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CoreThread_t qt_meta_stringdata_CoreThread = {
    {
QT_MOC_LITERAL(0, 0, 10) // "CoreThread"

    },
    "CoreThread"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CoreThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void CoreThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject CoreThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_CoreThread.data,
      qt_meta_data_CoreThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CoreThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CoreThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CoreThread.stringdata0))
        return static_cast<void*>(const_cast< CoreThread*>(this));
    return QThread::qt_metacast(_clname);
}

int CoreThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_CoreWorker_t {
    QByteArrayData data[8];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CoreWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CoreWorker_t qt_meta_stringdata_CoreWorker = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CoreWorker"
QT_MOC_LITERAL(1, 11, 10), // "onPODO2GUI"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 10), // "onGUI2PODO"
QT_MOC_LITERAL(4, 34, 13), // "onVISION2PODO"
QT_MOC_LITERAL(5, 48, 13), // "onPODO2VISION"
QT_MOC_LITERAL(6, 62, 10), // "onROS2PODO"
QT_MOC_LITERAL(7, 73, 10) // "onPODO2ROS"

    },
    "CoreWorker\0onPODO2GUI\0\0onGUI2PODO\0"
    "onVISION2PODO\0onPODO2VISION\0onROS2PODO\0"
    "onPODO2ROS"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CoreWorker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CoreWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CoreWorker *_t = static_cast<CoreWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onPODO2GUI(); break;
        case 1: _t->onGUI2PODO(); break;
        case 2: _t->onVISION2PODO(); break;
        case 3: _t->onPODO2VISION(); break;
        case 4: _t->onROS2PODO(); break;
        case 5: _t->onPODO2ROS(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CoreWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CoreWorker.data,
      qt_meta_data_CoreWorker,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CoreWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CoreWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CoreWorker.stringdata0))
        return static_cast<void*>(const_cast< CoreWorker*>(this));
    return QObject::qt_metacast(_clname);
}

int CoreWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
