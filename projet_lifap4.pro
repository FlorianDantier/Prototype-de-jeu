TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR += bin/

HEADERS += \
    src/common.h \
    src/Button.h \
    src/Game.h \
    src/Image.h \
    src/Menu.h \
    src/Rectangle.h \
    src/SDL_Game.h \
    src/Vec2.h \
    src/Character.h \
    src/Player.h \
    src/Enemy.h \
    src/Object.h \

SOURCES += \
    src/Button.cpp \
    src/Game.cpp \
    src/Menu.cpp \
    src/Rectangle.cpp \
    src/Image.cpp \
    src/SDL_Game.cpp \
    src/main.cpp \
    #src/mainTest.cpp \
    src/Character.cpp \
    src/Player.cpp \
    src/Enemy.cpp \
    src/Object.cpp \

LIBS += -L/usr/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
