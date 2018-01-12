TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp
QMAKE_CXXFLAGS += -std=c++17
QMAKE_CXXFLAGS += -msse4.2
