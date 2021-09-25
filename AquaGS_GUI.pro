QT       += core gui
QT       += concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    alphamate.cpp \
    blup.cpp \
    effect.cpp \
    main.cpp \
    mainwindow.cpp \
    phenotype.cpp \
    plink.cpp \
    process.cpp \
    start.cpp \
    tool.cpp

HEADERS += \
    alphamate.h \
    blup.h \
    effect.h \
    mainwindow.h \
    phenotype.h \
    plink.h \
    process.h \
    start.h \
    tool.h

FORMS += \
    mainwindow.ui

QMAKE_LFLAGS += -no-pie

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
