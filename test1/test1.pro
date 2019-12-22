TEMPLATE = app
CONFIG += console c++11 pthread
CONFIG -= app_bundle
CONFIG += qt mqtt

SOURCES += main.cpp
LIBS += -pthread
