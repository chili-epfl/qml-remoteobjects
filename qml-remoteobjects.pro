TEMPLATE = lib
TARGET = qmlremoteobjects

CONFIG += qt plugin c++11
CONFIG -= android_install

QT += qml quick remoteobjects

unix{
    QMAKE_CXXFLAGS -= -O2
    QMAKE_CXXFLAGS_RELEASE -= -O2

    QMAKE_CXXFLAGS += -O3
    QMAKE_CXXFLAGS_RELEASE += -O3
}

TARGET = $$qtLibraryTarget($$TARGET)
uri = QMLRemoteObjects

HEADERS += \
    src/QMLRemoteObjectsPlugin.h \
    src/RemoteObjectHost.h \
    src/RemoteObjectClient.h \
    src/RemoteObjectReplica.h

SOURCES += \
    src/QMLRemoteObjectsPlugin.cpp \
    src/RemoteObjectHost.cpp \
    src/RemoteObjectClient.cpp \
    src/RemoteObjectReplica.cpp

OTHER_FILES += qmldir

#Install plugin library, qmldir
qmldir.files = qmldir
installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
qmldir.path = $$installPath
target.path = $$installPath
INSTALLS += target qmldir
