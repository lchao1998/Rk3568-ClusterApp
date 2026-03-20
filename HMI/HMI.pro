QT += quick

CONFIG += c++17
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = HMI

HEADERS += \
    src/app_environment.h \
    src/DataModel.h

SOURCES += \
    src/main.cpp \

RESOURCES += \
    resource.qrc \
    qml.qrc

INCLUDEPATH += src/

# add log by source.
INCLUDEPATH += ../log/3rd/include \
               ../log/include


#CONFIG += SIMULATION

win32 {
    HEADERS += \
        src/win/BaseInfoDataModel.h \
        src/win/CenterViewDataModel.h \
        src/win/GaugeDataModel.h \
        src/win/TelltaleDataModel.h \
        src/win/WarningPopupDataModel.h

    SOURCES += \
        src/win/BaseInfoDataModel.cpp \
        src/win/CenterViewDataModel.cpp \
        src/win/GaugeDataModel.cpp \
        src/win/TelltaleDataModel.cpp \
        src/win/WarningPopupDataModel.cpp

    DEFINES += WINDOWS
}

else {
    SIMULATION {
        HEADERS += \
        src/linux/BaseInfoDataModel.h \
        src/linux/CenterViewDataModel.h \
        src/linux/GaugeDataModel.h \
        src/linux/TelltaleDataModel.h \
        src/linux/WarningPopupDataModel.h

        SOURCES += \
        src/linux/BaseInfoDataModel.cpp \
        src/linux/CenterViewDataModel.cpp \
        src/linux/GaugeDataModel.cpp \
        src/linux/TelltaleDataModel.cpp \
        src/linux/WarningPopupDataModel.cpp

        DEFINES += LINUX

        INCLUDEPATH +=  ../HMIControllers/interfaces \
                    ../HMIControllers/inc


        SOURCES +=  ../HMIControllers/src/sm_centerview.cpp\
                    ../HMIControllers/src/sm_telltalesm.cpp\
                    ../HMIControllers/src/sm_baseinfodata.cpp
    }

    else {
        HEADERS += \
        src/BaseInfoDataModel.h \
        src/CenterViewDataModel.h \
        src/GaugeDataModel.h \
        src/TelltaleDataModel.h \
        src/WarningPopupDataModel.h


        SOURCES += \
        src/BaseInfoDataModel.cpp \
        src/CenterViewDataModel.cpp \
        src/GaugeDataModel.cpp \
        src/TelltaleDataModel.cpp \
        src/WarningPopupDataModel.cpp

        INCLUDEPATH +=  ../HMIControllers/interfaces \
                    ../HMIControllers/inc


        SOURCES +=  ../HMIControllers/src/sm_telltalesm.cpp\
                ../HMIControllers/src/sm_centerview.cpp\
                ../HMIControllers/src/sm_baseinfodata.cpp\
                ../HMIControllers/src/sm_gaugedata.cpp\
                ../HMIControllers/src/sm_warningpopupdata.cpp
    }

    LIBS += -lzllog

}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

target.path=../release/usr/local/bin/hmi

target1.files += HMI
target1.path += /usr/local/bin/hmi

config.path=../release/usr/share/fonts
config.files += \
    ./content/fonts/*

INSTALLS += target config target1
