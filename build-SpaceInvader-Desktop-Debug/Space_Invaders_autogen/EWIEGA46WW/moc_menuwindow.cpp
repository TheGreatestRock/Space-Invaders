/****************************************************************************
** Meta object code from reading C++ file 'menuwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../SpaceInvader/menuwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'menuwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MenuWindow_t {
    QByteArrayData data[20];
    char stringdata0[389];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MenuWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MenuWindow_t qt_meta_stringdata_MenuWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MenuWindow"
QT_MOC_LITERAL(1, 11, 17), // "MainButtonClicked"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 30), // "handleColorBulletButtonClicked"
QT_MOC_LITERAL(4, 61, 31), // "handleColorInvaderButtonClicked"
QT_MOC_LITERAL(5, 93, 28), // "handleColorShipButtonClicked"
QT_MOC_LITERAL(6, 122, 29), // "handleShipEditorButtonClicked"
QT_MOC_LITERAL(7, 152, 32), // "handleInvaderEditorButtonClicked"
QT_MOC_LITERAL(8, 185, 31), // "handleBulletEditorButtonClicked"
QT_MOC_LITERAL(9, 217, 29), // "handleBackgroundButtonClicked"
QT_MOC_LITERAL(10, 247, 12), // "returnToMain"
QT_MOC_LITERAL(11, 260, 27), // "handleNbInvaderValueChanged"
QT_MOC_LITERAL(12, 288, 5), // "value"
QT_MOC_LITERAL(13, 294, 13), // "keyPressEvent"
QT_MOC_LITERAL(14, 308, 10), // "QKeyEvent*"
QT_MOC_LITERAL(15, 319, 5), // "event"
QT_MOC_LITERAL(16, 325, 15), // "keyReleaseEvent"
QT_MOC_LITERAL(17, 341, 18), // "handleDrawingSaved"
QT_MOC_LITERAL(18, 360, 23), // "QVector<QVector<bool> >"
QT_MOC_LITERAL(19, 384, 4) // "grid"

    },
    "MenuWindow\0MainButtonClicked\0\0"
    "handleColorBulletButtonClicked\0"
    "handleColorInvaderButtonClicked\0"
    "handleColorShipButtonClicked\0"
    "handleShipEditorButtonClicked\0"
    "handleInvaderEditorButtonClicked\0"
    "handleBulletEditorButtonClicked\0"
    "handleBackgroundButtonClicked\0"
    "returnToMain\0handleNbInvaderValueChanged\0"
    "value\0keyPressEvent\0QKeyEvent*\0event\0"
    "keyReleaseEvent\0handleDrawingSaved\0"
    "QVector<QVector<bool> >\0grid"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MenuWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    1,   88,    2, 0x08 /* Private */,
      13,    1,   91,    2, 0x08 /* Private */,
      16,    1,   94,    2, 0x08 /* Private */,
      17,    1,   97,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 18,   19,

       0        // eod
};

void MenuWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MenuWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->MainButtonClicked(); break;
        case 1: _t->handleColorBulletButtonClicked(); break;
        case 2: _t->handleColorInvaderButtonClicked(); break;
        case 3: _t->handleColorShipButtonClicked(); break;
        case 4: _t->handleShipEditorButtonClicked(); break;
        case 5: _t->handleInvaderEditorButtonClicked(); break;
        case 6: _t->handleBulletEditorButtonClicked(); break;
        case 7: _t->handleBackgroundButtonClicked(); break;
        case 8: _t->returnToMain(); break;
        case 9: _t->handleNbInvaderValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 11: _t->keyReleaseEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 12: _t->handleDrawingSaved((*reinterpret_cast< const QVector<QVector<bool> >(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QVector<bool> > >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MenuWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MenuWindow::MainButtonClicked)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MenuWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_MenuWindow.data,
    qt_meta_data_MenuWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MenuWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MenuWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MenuWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MenuWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void MenuWindow::MainButtonClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
