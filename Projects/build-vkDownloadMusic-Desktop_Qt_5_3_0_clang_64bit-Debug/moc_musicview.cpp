/****************************************************************************
** Meta object code from reading C++ file 'musicview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../vkDownloadMusic/musicview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'musicview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MusicView_t {
    QByteArrayData data[27];
    char stringdata[434];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MusicView_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MusicView_t qt_meta_stringdata_MusicView = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 8),
QT_MOC_LITERAL(2, 19, 0),
QT_MOC_LITERAL(3, 20, 31),
QT_MOC_LITERAL(4, 52, 16),
QT_MOC_LITERAL(5, 69, 4),
QT_MOC_LITERAL(6, 74, 31),
QT_MOC_LITERAL(7, 106, 8),
QT_MOC_LITERAL(8, 115, 34),
QT_MOC_LITERAL(9, 150, 18),
QT_MOC_LITERAL(10, 169, 27),
QT_MOC_LITERAL(11, 197, 21),
QT_MOC_LITERAL(12, 219, 13),
QT_MOC_LITERAL(13, 233, 19),
QT_MOC_LITERAL(14, 253, 5),
QT_MOC_LITERAL(15, 259, 21),
QT_MOC_LITERAL(16, 281, 16),
QT_MOC_LITERAL(17, 298, 3),
QT_MOC_LITERAL(18, 302, 24),
QT_MOC_LITERAL(19, 327, 15),
QT_MOC_LITERAL(20, 343, 19),
QT_MOC_LITERAL(21, 363, 11),
QT_MOC_LITERAL(22, 375, 8),
QT_MOC_LITERAL(23, 384, 23),
QT_MOC_LITERAL(24, 408, 12),
QT_MOC_LITERAL(25, 421, 6),
QT_MOC_LITERAL(26, 428, 5)
    },
    "MusicView\0finished\0\0on_listWidget_itemDoubleClicked\0"
    "QListWidgetItem*\0item\0"
    "on_horizontalSlider_sliderMoved\0"
    "position\0on_listWidget_itemSelectionChanged\0"
    "on_setPath_clicked\0on_lineEdit_editingFinished\0"
    "on_downButton_clicked\0stateChangedH\0"
    "QMediaPlayer::State\0state\0"
    "on_play_pause_clicked\0positionChangedH\0"
    "pos\0on_curPlayer_sliderMoved\0"
    "on_next_clicked\0on_previous_clicked\0"
    "oneDownload\0setMusic\0on_downButton_2_clicked\0"
    "getPartSongs\0offset\0count"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MusicView[] = {

 // content:
       7,       // revision
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
       3,    1,  100,    2, 0x08 /* Private */,
       6,    1,  103,    2, 0x08 /* Private */,
       8,    0,  106,    2, 0x08 /* Private */,
       9,    0,  107,    2, 0x08 /* Private */,
      10,    0,  108,    2, 0x08 /* Private */,
      11,    0,  109,    2, 0x08 /* Private */,
      12,    1,  110,    2, 0x08 /* Private */,
      15,    0,  113,    2, 0x08 /* Private */,
      16,    1,  114,    2, 0x08 /* Private */,
      18,    1,  117,    2, 0x08 /* Private */,
      19,    0,  120,    2, 0x08 /* Private */,
      20,    0,  121,    2, 0x08 /* Private */,
      21,    0,  122,    2, 0x08 /* Private */,
      22,    0,  123,    2, 0x08 /* Private */,
      23,    0,  124,    2, 0x08 /* Private */,
      24,    2,  125,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,   17,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   25,   26,

       0        // eod
};

void MusicView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MusicView *_t = static_cast<MusicView *>(_o);
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->on_listWidget_itemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->on_horizontalSlider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_listWidget_itemSelectionChanged(); break;
        case 4: _t->on_setPath_clicked(); break;
        case 5: _t->on_lineEdit_editingFinished(); break;
        case 6: _t->on_downButton_clicked(); break;
        case 7: _t->stateChangedH((*reinterpret_cast< QMediaPlayer::State(*)>(_a[1]))); break;
        case 8: _t->on_play_pause_clicked(); break;
        case 9: _t->positionChangedH((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 10: _t->on_curPlayer_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_next_clicked(); break;
        case 12: _t->on_previous_clicked(); break;
        case 13: _t->oneDownload(); break;
        case 14: _t->setMusic(); break;
        case 15: _t->on_downButton_2_clicked(); break;
        case 16: _t->getPartSongs((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMediaPlayer::State >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MusicView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MusicView::finished)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject MusicView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MusicView.data,
      qt_meta_data_MusicView,  qt_static_metacall, 0, 0}
};


const QMetaObject *MusicView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MusicView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MusicView.stringdata))
        return static_cast<void*>(const_cast< MusicView*>(this));
    return QWidget::qt_metacast(_clname);
}

int MusicView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void MusicView::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
