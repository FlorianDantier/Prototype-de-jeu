TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR += bin/

HEADERS += \
    src/Button.h \
    #src/Game.hpp \
    src/Image.h \
    src/Menu.h \
    src/Rectangle.h \
    src/Vec2.h \
    #src/Character.h

SOURCES += \
    src/Button.cpp \
    src/Menu.cpp \
    src/Rectangle.cpp \
    src/Image.cpp \
    src/main.cpp \
    #src/Character.cpp \
    #src/Game.cpp \

LIBS += -L/usr/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
