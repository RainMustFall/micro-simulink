QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase c++20
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testnumericgraph.cpp

# Importing core library

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../core/release/ -lcore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../core/debug/ -lcore
else:unix: LIBS += -L$$OUT_PWD/../core/ -lcore

INCLUDEPATH += $$PWD/../core
DEPENDPATH += $$PWD/../core
