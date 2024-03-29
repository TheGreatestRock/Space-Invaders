/****************************************************************************
** Meta object code from reading C++ file 'menuwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../SpaceInvader/menuwindow.h"
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
    QByteArrayData data[26];
    char stringdata0[502];
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
QT_MOC_LITERAL(8, 185, 32), // "handlePowerEditorUpButtonClicked"
QT_MOC_LITERAL(9, 218, 31), // "handleBulletEditorButtonClicked"
QT_MOC_LITERAL(10, 250, 27), // "handleNbInvaderValueChanged"
QT_MOC_LITERAL(11, 278, 5), // "value"
QT_MOC_LITERAL(12, 284, 29), // "handleBackgroundButtonClicked"
QT_MOC_LITERAL(13, 314, 18), // "handleDrawingSaved"
QT_MOC_LITERAL(14, 333, 23), // "QVector<QVector<bool> >"
QT_MOC_LITERAL(15, 357, 4), // "grid"
QT_MOC_LITERAL(16, 362, 21), // "openColorPickerWindow"
QT_MOC_LITERAL(17, 384, 12), // "QPushButton*"
QT_MOC_LITERAL(18, 397, 6), // "button"
QT_MOC_LITERAL(19, 404, 13), // "keyPressEvent"
QT_MOC_LITERAL(20, 418, 10), // "QKeyEvent*"
QT_MOC_LITERAL(21, 429, 5), // "event"
QT_MOC_LITERAL(22, 435, 15), // "keyReleaseEvent"
QT_MOC_LITERAL(23, 451, 17), // "saveOptionsToFile"
QT_MOC_LITERAL(24, 469, 19), // "loadOptionsFromFile"
QT_MOC_LITERAL(25, 489, 12) // "returnToMain"

    },
    "MenuWindow\0MainButtonClicked\0\0"
    "handleColorBulletButtonClicked\0"
    "handleColorInvaderButtonClicked\0"
    "handleColorShipButtonClicked\0"
    "handleShipEditorButtonClicked\0"
    "handleInvaderEditorButtonClicked\0"
    "handlePowerEditorUpButtonClicked\0"
    "handleBulletEditorButtonClicked\0"
    "handleNbInvaderValueChanged\0value\0"
    "handleBackgroundButtonClicked\0"
    "handleDrawingSaved\0QVector<QVector<bool> >\0"
    "grid\0openColorPickerWindow\0QPushButton*\0"
    "button\0keyPressEvent\0QKeyEvent*\0event\0"
    "keyReleaseEvent\0saveOptionsToFile\0"
    "loadOptionsFromFile\0returnToMain"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MenuWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,  100,    2, 0x08 /* Private */,
       4,    0,  101,    2, 0x08 /* Private */,
       5,    0,  102,    2, 0x08 /* Private */,
       6,    0,  103,    2, 0x08 /* Private */,
       7,    0,  104,    2, 0x08 /* Private */,
       8,    0,  105,    2, 0x08 /* Private */,
       9,    0,  106,    2, 0x08 /* Private */,
      10,    1,  107,    2, 0x08 /* Private */,
      12,    0,  110,    2, 0x08 /* Private */,
      13,    1,  111,    2, 0x08 /* Private */,
      16,    1,  114,    2, 0x08 /* Private */,
      19,    1,  117,    2, 0x08 /* Private */,
      22,    1,  120,    2, 0x08 /* Private */,
      23,    0,  123,    2, 0x08 /* Private */,
      24,    0,  124,    2, 0x08 /* Private */,
      25,    0,  125,    2, 0x08 /* Private */,

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
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

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
        case 6: _t->handlePowerEditorUpButtonClicked(); break;
        case 7: _t->handleBulletEditorButtonClicked(); break;
        case 8: _t->handleNbInvaderValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->handleBackgroundButtonClicked(); break;
        case 10: _t->handleDrawingSaved((*reinterpret_cast< const QVector<QVector<bool> >(*)>(_a[1]))); break;
        case 11: _t->openColorPickerWindow((*reinterpret_cast< QPushButton*(*)>(_a[1]))); break;
        case 12: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 13: _t->keyReleaseEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 14: _t->saveOptionsToFile(); break;
        case 15: _t->loadOptionsFromFile(); break;
        case 16: _t->returnToMain(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QVector<bool> > >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QPushButton* >(); break;
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
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
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
