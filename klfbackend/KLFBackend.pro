#-------------------------------------------------
#
# Project created by QtCreator 2013-04-10T00:00:00
#
#-------------------------------------------------

QT       += core gui widgets core5compat

# KLF backend versions
KLF_BACKEND_VERSION = 3.2.8

DEFINES +=KLF_VERSION_STRING=\\\"$$KLF_BACKEND_VERSION\\\" \
        KLF_SRC_BUILD KLFBACKEND_QT4

TEMPLATE = lib

SOURCES += klfbackend.cpp \
    klfdebug.cpp \
    klfblockprocess.cpp \
    klfdefs.cpp \
    klfpreviewbuilderthread.cpp

HEADERS += klfbackend.h \
    klfqt34common.h \
    klfdefs.h \
    klfdebug.h \
    klfblockprocess.h \
    klfpreviewbuilderthread.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
