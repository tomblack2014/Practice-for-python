/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../RobitCoach/MainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata[356];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 10), // "setRefPara"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 6), // "string"
QT_MOC_LITERAL(4, 30, 2), // "ip"
QT_MOC_LITERAL(5, 33, 4), // "port"
QT_MOC_LITERAL(6, 38, 30), // "on_actionChange_Side_triggered"
QT_MOC_LITERAL(7, 69, 32), // "on_pushButton_ConnectREF_clicked"
QT_MOC_LITERAL(8, 102, 27), // "on_label_FieldMap_clickMove"
QT_MOC_LITERAL(9, 130, 1), // "x"
QT_MOC_LITERAL(10, 132, 1), // "y"
QT_MOC_LITERAL(11, 134, 2), // "ID"
QT_MOC_LITERAL(12, 137, 28), // "on_label_FieldMap_stopAction"
QT_MOC_LITERAL(13, 166, 27), // "on_label_FieldMap_shootBall"
QT_MOC_LITERAL(14, 194, 33), // "on_actionEmergency_Stop_trigg..."
QT_MOC_LITERAL(15, 228, 29), // "on_pushButton_KickOff_clicked"
QT_MOC_LITERAL(16, 258, 32), // "on_actionAttack_Action_triggered"
QT_MOC_LITERAL(17, 291, 33), // "on_actionStop_One_Agent_trigg..."
QT_MOC_LITERAL(18, 325, 30) // "on_pushButton_FreeKick_clicked"

    },
    "MainWindow\0setRefPara\0\0string\0ip\0port\0"
    "on_actionChange_Side_triggered\0"
    "on_pushButton_ConnectREF_clicked\0"
    "on_label_FieldMap_clickMove\0x\0y\0ID\0"
    "on_label_FieldMap_stopAction\0"
    "on_label_FieldMap_shootBall\0"
    "on_actionEmergency_Stop_triggered\0"
    "on_pushButton_KickOff_clicked\0"
    "on_actionAttack_Action_triggered\0"
    "on_actionStop_One_Agent_triggered\0"
    "on_pushButton_FreeKick_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   74,    2, 0x08 /* Private */,
       7,    0,   75,    2, 0x08 /* Private */,
       8,    3,   76,    2, 0x08 /* Private */,
      12,    1,   83,    2, 0x08 /* Private */,
      13,    1,   86,    2, 0x08 /* Private */,
      14,    0,   89,    2, 0x08 /* Private */,
      15,    0,   90,    2, 0x08 /* Private */,
      16,    0,   91,    2, 0x08 /* Private */,
      17,    0,   92,    2, 0x08 /* Private */,
      18,    0,   93,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    9,   10,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->setRefPara((*reinterpret_cast< string(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->on_actionChange_Side_triggered(); break;
        case 2: _t->on_pushButton_ConnectREF_clicked(); break;
        case 3: _t->on_label_FieldMap_clickMove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->on_label_FieldMap_stopAction((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_label_FieldMap_shootBall((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_actionEmergency_Stop_triggered(); break;
        case 7: _t->on_pushButton_KickOff_clicked(); break;
        case 8: _t->on_actionAttack_Action_triggered(); break;
        case 9: _t->on_actionStop_One_Agent_triggered(); break;
        case 10: _t->on_pushButton_FreeKick_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(string , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::setRefPara)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::setRefPara(string _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
