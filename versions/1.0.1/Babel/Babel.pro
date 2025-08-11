QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    LetterConverter.cpp \
    aboutdialog.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    LetterConverter.h \
    aboutdialog.h \
    mainwindow.h

FORMS += \
    aboutdialog.ui \
    mainwindow.ui

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

# 修复自动生成QM文件的配置
QM_DIR = $$PWD


# 确保在编译时生成QM文件
PRE_TARGETDEPS += $$QM_FILES

# 可选：将生成的QM文件添加到部署文件列表
DISTFILES += $$QM_FILES
