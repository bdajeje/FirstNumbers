TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

LIBS += -lboost_system -lboost_filesystem -lboost_thread

SOURCES += main.cpp \
    core/first_numbers.cpp \
    utils/files.cpp \
    utils/arguments.cpp \
    utils/help.cpp

HEADERS += \
    utils/arguments.hpp \
    core/first_numbers.hpp \
    utils/types.hpp \
    utils/files.hpp \
    utils/help.hpp

