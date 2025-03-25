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
    output_connection_point.cpp \
    visual_node.cpp

HEADERS += \
    connection.h \
    connection_point.h \
    graph_widget.h \
    input_connection_point.h \
    mainwindow.h \
    output_connection_point.h \
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
