TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR += bin/

HEADERS += \
    src/Game.hpp \
    src/Image.h \
    src/Rectangle.h \
    src/Vec2.h

SOURCES += \
    src/Rectangle.cpp \
    src/Image.cpp \
    src/main.cpp \
    src/Game.cpp \

LIBS += -L/usr/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
