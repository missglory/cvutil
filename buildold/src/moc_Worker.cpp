/****************************************************************************
** Meta object code from reading C++ file 'Worker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/Worker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Worker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Worker_t {
    QByteArrayData data[20];
    char stringdata0[176];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Worker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Worker_t qt_meta_stringdata_Worker = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Worker"
QT_MOC_LITERAL(1, 7, 9), // "sendFrame"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 14), // "frameProcessed"
QT_MOC_LITERAL(4, 33, 15), // "sendProcessTime"
QT_MOC_LITERAL(5, 49, 4), // "time"
QT_MOC_LITERAL(6, 54, 10), // "sendCenter"
QT_MOC_LITERAL(7, 65, 1), // "x"
QT_MOC_LITERAL(8, 67, 1), // "y"
QT_MOC_LITERAL(9, 69, 5), // "order"
QT_MOC_LITERAL(10, 75, 12), // "sendDiameter"
QT_MOC_LITERAL(11, 88, 1), // "d"
QT_MOC_LITERAL(12, 90, 14), // "sendCenterDist"
QT_MOC_LITERAL(13, 105, 4), // "dist"
QT_MOC_LITERAL(14, 110, 12), // "sendVariance"
QT_MOC_LITERAL(15, 123, 3), // "var"
QT_MOC_LITERAL(16, 127, 16), // "sendEccentricity"
QT_MOC_LITERAL(17, 144, 5), // "value"
QT_MOC_LITERAL(18, 150, 16), // "receiveGrabFrame"
QT_MOC_LITERAL(19, 167, 8) // "fileName"

    },
    "Worker\0sendFrame\0\0frameProcessed\0"
    "sendProcessTime\0time\0sendCenter\0x\0y\0"
    "order\0sendDiameter\0d\0sendCenterDist\0"
    "dist\0sendVariance\0var\0sendEccentricity\0"
    "value\0receiveGrabFrame\0fileName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Worker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,
       6,    3,   60,    2, 0x06 /* Public */,
      10,    2,   67,    2, 0x06 /* Public */,
      12,    1,   72,    2, 0x06 /* Public */,
      14,    1,   75,    2, 0x06 /* Public */,
      16,    1,   78,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      18,    1,   81,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QImage,    3,
    QMetaType::Void, QMetaType::Float,    5,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Int,    7,    8,    9,
    QMetaType::Void, QMetaType::Double, QMetaType::Int,   11,    9,
    QMetaType::Void, QMetaType::Double,   13,
    QMetaType::Void, QMetaType::Double,   15,
    QMetaType::Void, QMetaType::Double,   17,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   19,

       0        // eod
};

void Worker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Worker *_t = static_cast<Worker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendFrame((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 1: _t->sendProcessTime((*reinterpret_cast< const float(*)>(_a[1]))); break;
        case 2: _t->sendCenter((*reinterpret_cast< const float(*)>(_a[1])),(*reinterpret_cast< const float(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3]))); break;
        case 3: _t->sendDiameter((*reinterpret_cast< const double(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 4: _t->sendCenterDist((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 5: _t->sendVariance((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 6: _t->sendEccentricity((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 7: _t->receiveGrabFrame((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Worker::*)(const QImage & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Worker::sendFrame)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Worker::*)(const float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Worker::sendProcessTime)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Worker::*)(const float , const float , const int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Worker::sendCenter)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Worker::*)(const double , const int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Worker::sendDiameter)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Worker::*)(const double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Worker::sendCenterDist)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Worker::*)(const double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Worker::sendVariance)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Worker::*)(const double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Worker::sendEccentricity)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Worker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Worker.data,
      qt_meta_data_Worker,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Worker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Worker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Worker.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Worker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void Worker::sendFrame(const QImage & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Worker::sendProcessTime(const float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Worker::sendCenter(const float _t1, const float _t2, const int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Worker::sendDiameter(const double _t1, const int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Worker::sendCenterDist(const double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Worker::sendVariance(const double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Worker::sendEccentricity(const double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
