CONFIG -= qt

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    binary_operator.cpp \
    execution_result.cpp \
    function.cpp \
    scalar.cpp \
    scalar_node.cpp \
    scalar_result_factory.cpp \
    x_node.cpp

HEADERS += \
    binary_operator.h \
    execution_result.h \
    execution_result_factory.h \
    function.h \
    node.h \
    scalar.h \
    scalar_node.h \
    scalar_result_factory.h \
    x_node.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
