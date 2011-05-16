######################################################################
# Automatically generated by qmake (2.01a) Sa. Apr 9 03:33:48 2011
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . src/gui
INCLUDEPATH += . src/gui

# Input
HEADERS += src/gui/avatarWidget.h src/gui/BaghChal.h src/gui/boxWidget.h \
    src/gui/helpWindow.h \
    src/gui/infoWindow.h \
    src/gui/turnMsgBox.h \
    src/logic/Tiger.h \
    src/logic/PlayerTiger.h \
    src/logic/PlayerGoat.h \
    src/logic/Player.h \
    src/logic/Grid.h \
    src/logic/Goat.h \
    src/logic/Game.h \
    src/logic/FileIO.h \
    src/logic/Exceptions.h \
    src/logic/Enums.h \
    src/logic/Cell.h
FORMS += BaghChal.ui \
    helpWindow.ui \
    infoWindow.ui
SOURCES += main.cpp \
           src/gui/avatarWidget.cpp \
           src/gui/BaghChal.cpp \
           src/gui/boxWidget.cpp \
    src/gui/helpWindow.cpp \
    src/gui/infoWindow.cpp \
    src/gui/turnMsgBox.cpp \
    src/logic/Tiger.cpp \
    src/logic/PlayerTiger.cpp \
    src/logic/PlayerGoat.cpp \
    src/logic/Grid.cpp \
    src/logic/Goat.cpp \
    src/logic/Game.cpp \
    src/logic/FileIO.cpp \
    src/logic/Cell.cpp
RESOURCES += FileContainer.qrc