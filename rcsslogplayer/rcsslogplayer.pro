
TEMPLATE = lib
TARGET = rcssrcgparser
DESTDIR = ../lib
DEPENDPATH += .
INCLUDEPATH += . .. ../../boost_1_34_1
LIBS +=

DEFINES += HAVE_LIBZ
win32 {
  DEFINES += HAVE_WINDOWS_H
}
unix {
  DEFINES += HAVE_NETINET_IN_H
}

CONFIG += staticlib warn_on release

#QMAKE_LFLAGS_DEBUG += -static
#QMAKE_LFLAGS_DEBUG += -pg
#QMAKE_CFLAGS_DEBUG += -pg -static -DQABSTRACTSOCKET_DEBUG
#QMAKE_CXXFLAGS_DEBUG += -pg -static -DQABSTRACTSOCKET_DEBUG

# Input
HEADERS += \
    gzfstream.h \
    handler.h \
    parser.h \
    types.h \
    util.h

SOURCES += \
    gzfstream.cpp \
    parser.cpp \
    types.cpp \
    util.cpp
