QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
QMAKE_CXXFLAGS += -O3

win32: {
    QMAKE_CXXFLAGS_RELEASE -= -O2
    QMAKE_CXXFLAGS_RELEASE += -O3 -march=native -fopenmp
    QMAKE_LFLAGS_RELEASE += -fopenmp
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    colorconverter.cpp \
    linearconverter.cpp \
    main.cpp \
    mainwindow.cpp \
    smoothlife.cpp \
    updatableframe.cpp \
    worleybase.cpp

HEADERS += \
    colorconverter.h \
    linearconverter.h \
    mainwindow.h \
    smoothlife.h \
    updatableframe.h \
    worleybase.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
