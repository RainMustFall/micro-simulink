QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    algebraic_visual_nodes.cpp \
    calculation_widget.cpp \
    connection.cpp \
    connection_point.cpp \
    graph_widget.cpp \
    input_connection_point.cpp \
    integral_visual_node.cpp \
    latex_display_widget.cpp \
    main.cpp \
    mainwindow.cpp \
    node_drag_buffer.cpp \
    node_palette.cpp \
    number_visual_node.cpp \
    output_connection_point.cpp \
    root_visual_node.cpp \
    text_visual_node.cpp \
    trigonometry_visual_nodes.cpp \
    visual_binary_operator.cpp \
    visual_negation_operator.cpp \
    visual_node.cpp \
    x_visual_node.cpp

HEADERS += \
    algebraic_visual_nodes.h \
    calculation_widget.h \
    connection.h \
    connection_point.h \
    graph_widget.h \
    input_connection_point.h \
    integral_visual_node.h \
    latex_display_widget.h \
    mainwindow.h \
    node_drag_buffer.h \
    node_palette.h \
    number_visual_node.h \
    output_connection_point.h \
    root_visual_node.h \
    text_visual_node.h \
    trigonometry_visual_nodes.h \
    visual_binary_operator.h \
    visual_negation_operator.h \
    visual_node.h \
    x_visual_node.h

TRANSLATIONS += \
    app_en_US.ts
QMAKE_LRELEASE_FLAGS = -idbased
CONFIG += lrelease embed_translations

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

DEFINES += KLF_SRC_BUILD


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../klfbackend/release/ -lKLFBackend
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../klfbackend/debug/ -lKLFBackend
else:unix: LIBS += -L$$OUT_PWD/../klfbackend/ -lKLFBackend

INCLUDEPATH += $$PWD/../klfbackend
DEPENDPATH += $$PWD/../klfbackend
