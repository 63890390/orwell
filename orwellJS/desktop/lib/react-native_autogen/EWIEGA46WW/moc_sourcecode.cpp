/****************************************************************************
** Meta object code from reading C++ file 'sourcecode.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../node_modules/react-native/ReactQt/runtime/src/sourcecode.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sourcecode.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SourceCode_t {
    QByteArrayData data[14];
    char stringdata0[186];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SourceCode_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SourceCode_t qt_meta_stringdata_SourceCode = {
    {
QT_MOC_LITERAL(0, 0, 10), // "SourceCode"
QT_MOC_LITERAL(1, 11, 16), // "scriptUrlChanged"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 17), // "sourceCodeChanged"
QT_MOC_LITERAL(4, 47, 17), // "retryCountChanged"
QT_MOC_LITERAL(5, 65, 10), // "loadFailed"
QT_MOC_LITERAL(6, 76, 13), // "getScriptText"
QT_MOC_LITERAL(7, 90, 13), // "REACT_PROMISE"
QT_MOC_LITERAL(8, 104, 34), // "ModuleInterface::ListArgument..."
QT_MOC_LITERAL(9, 139, 7), // "resolve"
QT_MOC_LITERAL(10, 147, 6), // "reject"
QT_MOC_LITERAL(11, 154, 9), // "scriptURL"
QT_MOC_LITERAL(12, 164, 10), // "sourceCode"
QT_MOC_LITERAL(13, 175, 10) // "retryCount"

    },
    "SourceCode\0scriptUrlChanged\0\0"
    "sourceCodeChanged\0retryCountChanged\0"
    "loadFailed\0getScriptText\0REACT_PROMISE\0"
    "ModuleInterface::ListArgumentBlock\0"
    "resolve\0reject\0scriptURL\0sourceCode\0"
    "retryCount"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SourceCode[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       3,   48, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,
       4,    0,   41,    2, 0x06 /* Public */,
       5,    0,   42,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       6,    2,   43,    7, 0x00 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 8,    9,   10,

 // properties: name, type, flags
      11, QMetaType::QUrl, 0x00095401,
      12, QMetaType::QByteArray, 0x00491001,
      13, QMetaType::Int, 0x00491103,

 // properties: notify_signal_id
       0,
       1,
       2,

       0        // eod
};

void SourceCode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SourceCode *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->scriptUrlChanged(); break;
        case 1: _t->sourceCodeChanged(); break;
        case 2: _t->retryCountChanged(); break;
        case 3: _t->loadFailed(); break;
        case 4: _t->getScriptText((*reinterpret_cast< const ModuleInterface::ListArgumentBlock(*)>(_a[1])),(*reinterpret_cast< const ModuleInterface::ListArgumentBlock(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ModuleInterface::ListArgumentBlock >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SourceCode::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SourceCode::scriptUrlChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SourceCode::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SourceCode::sourceCodeChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SourceCode::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SourceCode::retryCountChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SourceCode::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SourceCode::loadFailed)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<SourceCode *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QUrl*>(_v) = _t->scriptUrl(); break;
        case 1: *reinterpret_cast< QByteArray*>(_v) = _t->sourceCode(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->retryCount(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<SourceCode *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 2: _t->setRetryCount(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject SourceCode::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_SourceCode.data,
    qt_meta_data_SourceCode,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SourceCode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SourceCode::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SourceCode.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ModuleInterface"))
        return static_cast< ModuleInterface*>(this);
    if (!strcmp(_clname, "com.canonical.ReactNative.ModuleInterface"))
        return static_cast< ModuleInterface*>(this);
    return QObject::qt_metacast(_clname);
}

int SourceCode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void SourceCode::scriptUrlChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SourceCode::sourceCodeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SourceCode::retryCountChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void SourceCode::loadFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
