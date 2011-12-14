/****************************************************************************
** Meta object code from reading C++ file 'editwindow.h'
**
** Created: Tue Dec 13 16:47:34 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/editwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EditWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      22,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_EditWindow[] = {
    "EditWindow\0\0ZoomOut()\0ZoomIn()\0"
};

const QMetaObject EditWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_EditWindow,
      qt_meta_data_EditWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EditWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EditWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EditWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EditWindow))
        return static_cast<void*>(const_cast< EditWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int EditWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ZoomOut(); break;
        case 1: ZoomIn(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
