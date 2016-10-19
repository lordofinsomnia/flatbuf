TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

HEADERS += \
    monster_generated.h

DISTFILES += \
    monster.idl \
    monster.json
