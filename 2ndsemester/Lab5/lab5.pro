QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    card.cpp \
    lib.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    card.h \
    lib.h \
    mainwindow.h

FORMS += \
    card.ui \
    mainwindow.ui