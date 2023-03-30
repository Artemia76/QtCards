QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

GIT_REVISION='\\"$$system(git rev-parse --short HEAD)\\"'

# Application Version
VERSION_MAJOR = 1
VERSION_MINOR = 0

DEFINES += APP_NAME=\\\"$${TARGET}\\\"
DEFINES += APP_MAJOR=$$VERSION_MAJOR
DEFINES += APP_MINOR=$$VERSION_MINOR
DEFINES += APP_BUILD=$$GIT_REVISION

SOURCES += \
    main.cpp \
    gui/mainwindow.cpp \
    tools/clogger.cpp \
    tools/datetime.cpp \
    tools/getappversion.cpp

HEADERS += \
    gui/mainwindow.h \
    tools/call_once.h \
    tools/clogger.h \
    tools/datetime.h \
    tools/getappversion.h \
    tools/singleton.h \
    tools/version.h

FORMS += \
    gui/mainwindow.ui

TRANSLATIONS += \
    i18n/QtCards_fr_FR.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qtcards.qrc

DISTFILES += \
    LICENSE \
    README.md
