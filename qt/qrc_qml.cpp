/****************************************************************************
** Resource object code
**
** Created by: The Resource Compiler for Qt version 5.11.2
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

static const unsigned char qt_resource_data[] = {
  // /home/lz/orwell/qt/main.qml
  0x0,0x0,0x0,0xcd,
  0x0,
  0x0,0x2,0xc4,0x78,0x9c,0xcd,0x91,0xcd,0xa,0xc2,0x30,0x10,0x84,0xef,0x79,0x8a,
  0xe0,0x3,0xa4,0xd9,0x34,0xad,0x26,0x27,0xf1,0xe2,0x51,0xbc,0x78,0x95,0xd2,0x1f,
  0xbb,0xd8,0xa6,0x21,0x4d,0xf5,0x20,0x7d,0x77,0xb5,0x45,0x2d,0x22,0x1e,0xc5,0xbd,
  0x7d,0x33,0xcc,0x30,0xb0,0x58,0xdb,0xc6,0x79,0xba,0xf5,0xdb,0xe,0xd3,0x23,0x15,
  0x8c,0x13,0x1c,0xa5,0x8d,0xcd,0xcd,0xba,0xda,0x61,0x96,0x37,0xf,0x17,0xde,0xdd,
  0x55,0x57,0x14,0xb9,0x9b,0xda,0x64,0xed,0x30,0xa3,0x17,0x42,0x6f,0x97,0x36,0x55,
  0x57,0x9b,0x56,0x53,0x31,0x60,0x6b,0x93,0x14,0xcd,0xe1,0x86,0x77,0x1a,0xa4,0x33,
  0x66,0xbe,0xd4,0x14,0xc4,0x82,0xf,0x5c,0xe6,0x78,0x28,0xbd,0xa6,0x73,0x31,0xf2,
  0x87,0xd,0x63,0xf5,0x24,0x1c,0x4b,0xfe,0x94,0x1e,0xf9,0x30,0x7e,0x69,0x9d,0x43,
  0x4d,0x67,0xce,0xb7,0x56,0x7,0x41,0x92,0xd5,0x68,0x34,0x28,0x25,0x54,0xa8,0xe4,
  0x12,0x94,0x60,0x10,0x2f,0x18,0x67,0xc0,0x43,0xd,0x3c,0x8a,0x64,0xe0,0x53,0x1b,
  0x24,0x27,0xbe,0xe7,0xb3,0xa1,0xa2,0xff,0xf9,0x10,0xf8,0x97,0x21,0xf2,0x1f,0x86,
  0x0,0x93,0x5f,0x3f,0x43,0x7a,0x72,0x5,0xb5,0xf8,0xb8,0x3,
  
};

static const unsigned char qt_resource_name[] = {
  // main.qml
  0x0,0x8,
  0x8,0x1,0x5a,0x5c,
  0x0,0x6d,
  0x0,0x61,0x0,0x69,0x0,0x6e,0x0,0x2e,0x0,0x71,0x0,0x6d,0x0,0x6c,
  
};

static const unsigned char qt_resource_struct[] = {
  // :
  0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x1,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  // :/main.qml
  0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,
0x0,0x0,0x1,0x69,0x6a,0x6b,0xf,0xf7,

};

#ifdef QT_NAMESPACE
#  define QT_RCC_PREPEND_NAMESPACE(name) ::QT_NAMESPACE::name
#  define QT_RCC_MANGLE_NAMESPACE0(x) x
#  define QT_RCC_MANGLE_NAMESPACE1(a, b) a##_##b
#  define QT_RCC_MANGLE_NAMESPACE2(a, b) QT_RCC_MANGLE_NAMESPACE1(a,b)
#  define QT_RCC_MANGLE_NAMESPACE(name) QT_RCC_MANGLE_NAMESPACE2( \
        QT_RCC_MANGLE_NAMESPACE0(name), QT_RCC_MANGLE_NAMESPACE0(QT_NAMESPACE))
#else
#   define QT_RCC_PREPEND_NAMESPACE(name) name
#   define QT_RCC_MANGLE_NAMESPACE(name) name
#endif

#ifdef QT_NAMESPACE
namespace QT_NAMESPACE {
#endif

bool qRegisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);

bool qUnregisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);

#ifdef QT_NAMESPACE
}
#endif

int QT_RCC_MANGLE_NAMESPACE(qInitResources_qml)();
int QT_RCC_MANGLE_NAMESPACE(qInitResources_qml)()
{
    QT_RCC_PREPEND_NAMESPACE(qRegisterResourceData)
        (0x2, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_qml)();
int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_qml)()
{
    QT_RCC_PREPEND_NAMESPACE(qUnregisterResourceData)
       (0x2, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

namespace {
   struct initializer {
       initializer() { QT_RCC_MANGLE_NAMESPACE(qInitResources_qml)(); }
       ~initializer() { QT_RCC_MANGLE_NAMESPACE(qCleanupResources_qml)(); }
   } dummy;
}
