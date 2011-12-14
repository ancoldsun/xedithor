/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Tue Dec 13 00:45:06 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      22,   11,   11,   11, 0x08,
      34,   11,   29,   11, 0x08,
      41,   11,   29,   11, 0x08,
      50,   11,   11,   11, 0x08,
      58,   11,   11,   11, 0x08,
      66,   11,   11,   11, 0x08,
      80,   11,   11,   11, 0x08,
      96,   11,   11,   11, 0x08,
     110,   11,   11,   11, 0x08,
     123,   11,   11,   11, 0x08,
     138,   11,   11,   11, 0x08,
     152,   11,   11,   11, 0x08,
     175,  169,   11,   11, 0x0a,
     219,  205,   11,   11, 0x0a,
     263,  259,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0newFile()\0open()\0bool\0"
    "save()\0saveAs()\0about()\0print()\0"
    "Add_Clicked()\0Clone_Clicked()\0"
    "Del_Clicked()\0Up_Clicked()\0Down_Clicked()\0"
    "Top_Clicked()\0Bottom_Clicked()\0index\0"
    "tableRowSelected(QModelIndex)\0"
    "indexA,indexB\0UpdateDataCell(QModelIndex,QModelIndex)\0"
    "str\0TableEditCompleted(QString)\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newFile(); break;
        case 1: open(); break;
        case 2: { bool _r = save();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = saveAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: about(); break;
        case 5: print(); break;
        case 6: Add_Clicked(); break;
        case 7: Clone_Clicked(); break;
        case 8: Del_Clicked(); break;
        case 9: Up_Clicked(); break;
        case 10: Down_Clicked(); break;
        case 11: Top_Clicked(); break;
        case 12: Bottom_Clicked(); break;
        case 13: tableRowSelected((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 14: UpdateDataCell((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2]))); break;
        case 15: TableEditCompleted((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
