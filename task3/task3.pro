QT += core gui network printsupport widgets

TARGET = ../build/task3
TEMPLATE = app

CONFIG += c++11

SOURCES +=\
    main.cpp \
    cpu_graph.cpp \
    qcustomplot.cpp

HEADERS  += cpu_graph.h \
    qcustomplot.h
