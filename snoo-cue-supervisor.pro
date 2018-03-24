QT       += core gui serialport printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = snoo-cue-supervisor
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS += -Wno-missing-field-initializers

INCLUDEPATH += deps/snoo-cue-protocol/include
INCLUDEPATH += deps/QCustomPlot

SOURCES += \
        src/main.cpp \
        src/SupervisorMainWindow.cpp \
        deps/snoo-cue-protocol/src/protocol_debug.c \
        deps/snoo-cue-protocol/src/protocol.c \
        deps/QCustomPlot/qcustomplot.cpp \
    src/ImuSensor.cpp \
    src/PlottingHelpers.cpp

HEADERS += \
        src/SupervisorMainWindow.h \
        deps/snoo-cue-protocol/include/protocol_debug.h \
        deps/snoo-cue-protocol/include/protocol.h \
        deps/QCustomPlot/qcustomplot.h \
    src/ImuSensor.h \
    src/PlottingHelpers.h


FORMS += \
        ui/supervisormainwindow.ui
