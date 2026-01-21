QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++17 static static_runtime no-exceptions no-rtti embed_translations lrelease


QT_CONFIG -= accessibility concurrent dbus network printsupport sql testlib


QMAKE_CFLAGS_RELEASE -= -O0
QMAKE_CFLAGS_RELEASE += -O2
QMAKE_CXXFLAGS_RELEASE -= -O0
QMAKE_CXXFLAGS_RELEASE += -O2

QMAKE_CXXFLAGS_RELEASE += -ffunction-sections -fdata-sections
QMAKE_LFLAGS_RELEASE += -Wl,--gc-sections

CONFIG += ninja
CONFIG += lto


DESTDIR = $PWD/build


OBJECTS_DIR = $PWD/build/obj
MOC_DIR = $PWD/build/moc
RCC_DIR = $PWD/build/rcc
UI_DIR = build/ui


win32 {
    copy_mappings.commands = $(COPY_DIR) $shell_path($PWD/resources/mappings.json) $shell_path($DESTDIR/)
} else:unix {
    copy_mappings.commands = cp -f $PWD/resources/mappings.json $DESTDIR/
}

QMAKE_EXTRA_TARGETS += copy_mappings
POST_TARGETDEPS += copy_mappings

SOURCES += \
    src/LetterConverter.cpp \
    src/aboutdialog.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/phoneticchartdialog.cpp

HEADERS += \
    include/LetterConverter.h \
    include/aboutdialog.h \
    include/mainwindow.h \
    include/phoneticchartdialog.h

INCLUDEPATH += include

FORMS += \
    ui/aboutdialog.ui \
    ui/mainwindow.ui \
    ui/phoneticchartdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_FILE = resources/logo.rc
RC_ICON = resources/app.ico

DISTFILES += \
    resources/logo.rc \
    resources/mappings.json

RESOURCES += \
    resources/res.qrc

TRANSLATIONS += \
    translations/Babel_ar_SA.ts \
    translations/Babel_en_US.ts \
    translations/Babel_es_ES.ts \
    translations/Babel_fr_FR.ts \
    translations/Babel_ru_RU.ts \
    translations/Babel_zh_CN.ts
