QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++17 static static_runtime no-exceptions no-rtti embed_translations lrelease


QT_CONFIG -= accessibility concurrent dbus network printsupport sql testlib

# 启用 O2 优化
QMAKE_CFLAGS_RELEASE -= -O0
QMAKE_CFLAGS_RELEASE += -O2
QMAKE_CXXFLAGS_RELEASE -= -O0
QMAKE_CXXFLAGS_RELEASE += -O2

# 在文件顶部添加
CONFIG += ninja

SOURCES += \
    LetterConverter.cpp \
    aboutdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    phoneticchartdialog.cpp

HEADERS += \
    LetterConverter.h \
    aboutdialog.h \
    mainwindow.h \
    phoneticchartdialog.h

FORMS += \
    aboutdialog.ui \
    mainwindow.ui \
    phoneticchartdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_FILE = logo.rc
RC_ICON = app.ico

DISTFILES += \
    logo.rc

RESOURCES += \
    res.qrc

TRANSLATIONS += \
    Babel_ar_SA.ts \
    Babel_en_US.ts \
    Babel_es_ES.ts \
    Babel_fr_FR.ts \
    Babel_ru_RU.ts \
    Babel_zh_CN.ts
