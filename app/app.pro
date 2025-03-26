QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    connection.cpp \
    connection_point.cpp \
    graph_widget.cpp \
    input_connection_point.cpp \
    main.cpp \
    mainwindow.cpp \
    node_palette.cpp \
    number_visual_node.cpp \
    output_connection_point.cpp \
    root_visual_node.cpp \
    visual_node.cpp

HEADERS += \
    connection.h \
    connection_point.h \
    graph_widget.h \
    input_connection_point.h \
    mainwindow.h \
    node_palette.h \
    number_visual_node.h \
    output_connection_point.h \
    root_visual_node.h \
    visual_node.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    app_pl_PL.ts
CONFIG += lrelease
CONFIG += embed_translations

CONFIG+=sanitizer

CONFIG+=sanitize_address

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Importing core library

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../core/release/ -lcore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../core/debug/ -lcore
else:unix: LIBS += -L$$OUT_PWD/../core/ -lcore

INCLUDEPATH += $$PWD/../core
DEPENDPATH += $$PWD/../core

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../core/release/libcore.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../core/debug/libcore.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../core/release/core.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../core/debug/core.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../core/libcore.a
