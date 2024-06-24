/****************************************************************************
** Meta object code from reading C++ file 'quanly_tk.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../NhapXuatKho_CNDT/quanly_tk.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'quanly_tk.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QuanLy_TK_t {
    QByteArrayData data[13];
    char stringdata0[249];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QuanLy_TK_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QuanLy_TK_t qt_meta_stringdata_QuanLy_TK = {
    {
QT_MOC_LITERAL(0, 0, 9), // "QuanLy_TK"
QT_MOC_LITERAL(1, 10, 31), // "on_comboBox_currentIndexChanged"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 4), // "arg1"
QT_MOC_LITERAL(4, 48, 32), // "on_pushButton_BatDauThem_clicked"
QT_MOC_LITERAL(5, 81, 30), // "on_lineEdit_MatKhau_textEdited"
QT_MOC_LITERAL(6, 112, 35), // "on_lineEdit_MatKhau_editingFi..."
QT_MOC_LITERAL(7, 148, 21), // "on_pushButton_pressed"
QT_MOC_LITERAL(8, 170, 22), // "on_pushButton_released"
QT_MOC_LITERAL(9, 193, 25), // "on_pushButton_Luu_clicked"
QT_MOC_LITERAL(10, 219, 18), // "SectionDoubleClick"
QT_MOC_LITERAL(11, 238, 3), // "row"
QT_MOC_LITERAL(12, 242, 6) // "column"

    },
    "QuanLy_TK\0on_comboBox_currentIndexChanged\0"
    "\0arg1\0on_pushButton_BatDauThem_clicked\0"
    "on_lineEdit_MatKhau_textEdited\0"
    "on_lineEdit_MatKhau_editingFinished\0"
    "on_pushButton_pressed\0on_pushButton_released\0"
    "on_pushButton_Luu_clicked\0SectionDoubleClick\0"
    "row\0column"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QuanLy_TK[] = {

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
       1,    1,   54,    2, 0x08 /* Private */,
       4,    0,   57,    2, 0x08 /* Private */,
       5,    1,   58,    2, 0x08 /* Private */,
       6,    0,   61,    2, 0x08 /* Private */,
       7,    0,   62,    2, 0x08 /* Private */,
       8,    0,   63,    2, 0x08 /* Private */,
       9,    0,   64,    2, 0x08 /* Private */,
      10,    2,   65,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   11,   12,

       0        // eod
};

void QuanLy_TK::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QuanLy_TK *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_comboBox_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->on_pushButton_BatDauThem_clicked(); break;
        case 2: _t->on_lineEdit_MatKhau_textEdited((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_lineEdit_MatKhau_editingFinished(); break;
        case 4: _t->on_pushButton_pressed(); break;
        case 5: _t->on_pushButton_released(); break;
        case 6: _t->on_pushButton_Luu_clicked(); break;
        case 7: _t->SectionDoubleClick((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QuanLy_TK::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_QuanLy_TK.data,
    qt_meta_data_QuanLy_TK,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QuanLy_TK::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QuanLy_TK::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QuanLy_TK.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int QuanLy_TK::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
