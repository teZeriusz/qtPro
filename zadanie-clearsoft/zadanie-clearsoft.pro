TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp
QMAKE_CXXFLAGS += -std=c++17

DISTFILES += \
    deck.txt
