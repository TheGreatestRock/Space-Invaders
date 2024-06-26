QT       += widgets
QT       += multimedia


CONFIG   += c++17

TARGET = Space_Invaders
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

QT += network
DEPENDPATH += .
INCLUDEPATH += .

SOURCES += \
        main.cpp \
        gamewindow.cpp \
        player.cpp \
        bullet.cpp \
        invader.cpp \
        mainwindow.cpp \
        colorpickerwindow.cpp \
        menuwindow.cpp \
        powerup.cpp \
        titlewindow.cpp \
        winwindow.cpp \
        editorwindow.cpp

HEADERS += \
        gamewindow.h \
        player.h \
        bullet.h \
        invader.h \
        mainwindow.h \
        colorpickerwindow.h \
        menuwindow.h \
        powerup.h \
        titlewindow.h \
        winwindow.h \
        editorwindow.h

FORMS += \
        titlewindow.ui \
        mainwindow.ui

TS_FILES = Space_Invaders_fr_FR.ts

TRANSLATIONS = $$TS_FILES

# Bundle settings
QMAKE_BUNDLE_NAME = Space_Invaders
QMAKE_BUNDLE_IDENTIFIER = com.example.Space_Invaders
QMAKE_BUNDLE_VERSION = 0.1
QMAKE_BUNDLE_SHORT_VERSION_STRING = 0.1

# Install settings
target.path = /usr/local/bin
INSTALLS += target
