TEMPLATE = app
TARGET = go

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SUBDIRS += \
    go.pro

DISTFILES += \
    README.md \
    scratch.txt

HEADERS += \
    src/board.h \
    src/gameoverbox.h \
    src/mainwindow.h \
    src/square.h \
    src/enum.h \
    src/intersection.h \
    src/statusbarwidgets/turninfo.h \
    src/statusbarwidgets/xyinfo.h \
    src/stone.h \
    src/game.h

SOURCES += \
    src/board.cpp \
    src/gameoverbox.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/square.cpp \
    src/intersection.cpp \
    src/statusbarwidgets/turninfo.cpp \
    src/statusbarwidgets/xyinfo.cpp \
    src/stone.cpp \
    src/game.cpp
