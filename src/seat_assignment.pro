QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
CONFIG += console c++11

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG(release, debug|release) : TARGET = SeatAssignment
CONFIG(debug, debug|release) : TARGET = SeatAssignmentd

CONFIG(release, debug|release) : DESTDIR = $$_PRO_FILE_PWD_/../bin
CONFIG(debug, debug|release) : DESTDIR = $$_PRO_FILE_PWD_/../bin

SOURCES += \
    main.cpp \
    seatassigner.cpp \
    flight.cpp \
    sequentialassigner.cpp \
    randomassigner.cpp \
    manualassigner.cpp

HEADERS += \
    seatassigner.h \
    flight.h \
    sequentialassigner.h \
    randomassigner.h \
    commondata.h \
    exceptions.h \
    manualassigner.h

#uncomment following line to enable unit testing
#CONFIG += test
CONFIG(test) {

    QT += testlib

    INCLUDEPATH += $$_PRO_FILE_PWD_/../test/unit/src

    SOURCES += \
    ../test/unit/src/testflight.cpp \
    ../test/unit/src/testsequentialassigner.cpp \
    ../test/unit/src/testrandomassigner.cpp \
    ../test/unit/src/testmanualassigner.cpp

    HEADERS += \
    ../test/unit/src/testflight.h \
    ../test/unit/src/testsequentialassigner.h \
    ../test/unit/src/testrandomassigner.h \
    ../test/unit/src/testmanualassigner.h

    DEFINES += UNIT_TESTING

    DESTDIR = $$_PRO_FILE_PWD_/../test/unit/bin/

    TARGET = Seat_Assignment_Unit_Test
}
