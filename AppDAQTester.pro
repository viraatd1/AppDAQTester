QT += quick virtualkeyboard

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Paho C Libraries
INCLUDEPATH += $$PWD/externals/packages/include/
#LIBS += -L$$PWD/externals/packages/lib -lpaho-mqtt3a
LIBS += -L$$PWD/externals/packages/lib -lpaho-mqtt3as
#LIBS += -L$$PWD/externals/packages/lib -lpaho-mqtt3c
LIBS += -L$$PWD/externals/packages/lib -lpaho-mqtt3cs

# Paho CPP Libraries
#INCLUDEPATH += $$PWD/externals/packages/include/
LIBS += -L$$PWD/externals/packages/lib -lpaho-mqttpp3


# Sciton DAQ Library
#INCLUDEPATH += $$PWD/AppDAQTester/externals/packages/
#LIBS += -L$$PWD/externals/packages/

# Sciton DAQ Service Functionalities


SOURCES += \
        main.cpp \
        modules/moduleIQ/mqttclientmanager.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =


DISTFILES += \
    certs/cacert.pem \
    certs/cert.pem \
    certs/key.pem \
    configs/serverConfig.json \
    externals/config_library_essentials.sh

HEADERS += \
    modules/moduleIQ/mqttclientmanager.h
