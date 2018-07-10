/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[24];
    char stringdata0[277];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 12), // "requestFrame"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 8), // "fileName"
QT_MOC_LITERAL(4, 34, 9), // "sendFrame"
QT_MOC_LITERAL(5, 44, 8), // "filename"
QT_MOC_LITERAL(6, 53, 22), // "onButtonForwardClicked"
QT_MOC_LITERAL(7, 76, 19), // "onButtonBackClicked"
QT_MOC_LITERAL(8, 96, 12), // "receiveFrame"
QT_MOC_LITERAL(9, 109, 5), // "frame"
QT_MOC_LITERAL(10, 115, 19), // "onOpenButtonClicked"
QT_MOC_LITERAL(11, 135, 18), // "receiveProcessTime"
QT_MOC_LITERAL(12, 154, 4), // "time"
QT_MOC_LITERAL(13, 159, 15), // "receiveDiameter"
QT_MOC_LITERAL(14, 175, 1), // "d"
QT_MOC_LITERAL(15, 177, 5), // "order"
QT_MOC_LITERAL(16, 183, 13), // "receiveCenter"
QT_MOC_LITERAL(17, 197, 1), // "x"
QT_MOC_LITERAL(18, 199, 1), // "y"
QT_MOC_LITERAL(19, 201, 17), // "receiveCenterDist"
QT_MOC_LITERAL(20, 219, 15), // "receiveVariance"
QT_MOC_LITERAL(21, 235, 19), // "receiveEccentricity"
QT_MOC_LITERAL(22, 255, 3), // "val"
QT_MOC_LITERAL(23, 259, 17) // "receiveStartFrame"

    },
    "MainWindow\0requestFrame\0\0fileName\0"
    "sendFrame\0filename\0onButtonForwardClicked\0"
    "onButtonBackClicked\0receiveFrame\0frame\0"
    "onOpenButtonClicked\0receiveProcessTime\0"
    "time\0receiveDiameter\0d\0order\0receiveCenter\0"
    "x\0y\0receiveCenterDist\0receiveVariance\0"
    "receiveEccentricity\0val\0receiveStartFrame"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       4,    1,   82,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   85,    2, 0x08 /* Private */,
       7,    0,   86,    2, 0x08 /* Private */,
       8,    1,   87,    2, 0x08 /* Private */,
      10,    0,   90,    2, 0x08 /* Private */,
      11,    1,   91,    2, 0x08 /* Private */,
      13,    2,   94,    2, 0x08 /* Private */,
      16,    3,   99,    2, 0x08 /* Private */,
      19,    1,  106,    2, 0x08 /* Private */,
      20,    1,  109,    2, 0x08 /* Private */,
      21,    1,  112,    2, 0x08 /* Private */,
      23,    1,  115,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float,   12,
    QMetaType::Void, QMetaType::Double, QMetaType::Int,   14,   15,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Int,   17,   18,   15,
    QMetaType::Void, QMetaType::Double,   14,
    QMetaType::Void, QMetaType::Double,   14,
    QMetaType::Void, QMetaType::Double,   22,
    QMetaType::Void, QMetaType::QString,    5,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->requestFrame((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->sendFrame((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->onButtonForwardClicked(); break;
        case 3: _t->onButtonBackClicked(); break;
        case 4: _t->receiveFrame((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 5: _t->onOpenButtonClicked(); break;
        case 6: _t->receiveProcessTime((*reinterpret_cast< const float(*)>(_a[1]))); break;
        case 7: _t->receiveDiameter((*reinterpret_cast< const double(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 8: _t->receiveCenter((*reinterpret_cast< const float(*)>(_a[1])),(*reinterpret_cast< const float(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3]))); break;
        case 9: _t->receiveCenterDist((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 10: _t->receiveVariance((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 11: _t->receiveEccentricity((*reinterpret_cast< const double(*)>(_a[1]))); break;
        case 12: _t->receiveStartFrame((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::requestFrame)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sendFrame)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::requestFrame(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::sendFrame(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
