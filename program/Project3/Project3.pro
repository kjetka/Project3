TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    planet.cpp \
    solver.cpp

HEADERS += \
    planet.h \
    solver.h

INCLUDEPATH += D:\armadillo-8.100.1/include

INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib
LIBS += -larmadillo -llapack -lblas

#QMAKE_CXXFLAGS += -O3
#QMAKE_CXXFLAGS -= -O2
