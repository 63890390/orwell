/****************************************************************************
** Meta object code from reading C++ file 'imagemanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../node_modules/react-native/ReactQt/runtime/src/componentmanagers/imagemanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imagemanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ImageManager_t {
    QByteArrayData data[6];
    char stringdata0[57];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ImageManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ImageManager_t qt_meta_stringdata_ImageManager = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ImageManager"
QT_MOC_LITERAL(1, 13, 12), // "manageSource"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 11), // "imageSource"
QT_MOC_LITERAL(4, 39, 11), // "QQuickItem*"
QT_MOC_LITERAL(5, 51, 5) // "image"

    },
    "ImageManager\0manageSource\0\0imageSource\0"
    "QQuickItem*\0image"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImageManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QVariantMap, 0x80000000 | 4,    3,    5,

       0        // eod
};

void ImageManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ImageManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->manageSource((*reinterpret_cast< const QVariantMap(*)>(_a[1])),(*reinterpret_cast< QQuickItem*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QQuickItem* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ImageManager::staticMetaObject = { {
    &ViewManager::staticMetaObject,
    qt_meta_stringdata_ImageManager.data,
    qt_meta_data_ImageManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ImageManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ImageManager.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "com.canonical.ReactNative.ModuleInterface"))
        return static_cast< ModuleInterface*>(this);
    return ViewManager::qt_metacast(_clname);
}

int ImageManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ViewManager::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
