QT += core
QT += widgets
QT += gui
QT += multimedia

TARGET = Popstar
# CONFIG += console
CONFIG += c++14
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    game.cpp \
    start2.cpp \
    sound.cpp \
    help.cpp \
    about.cpp

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    main.h \
    game.h \
    start2.h \
    sound.h \
    help.h \
    about.h

RESOURCES += \
    resource.qrc
