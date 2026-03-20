

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: rectangle
    width: 1920
    height: 720
    color: "#00000000"

    Item {
        id: powerStatus_ON
        visible: true
        anchors.fill: parent

        Image {
            id: background
            x: 0
            y: 0
            visible: centerviewdatamodel.Menu_SwSta !== 3
                     && centerviewdatamodel.Menu_SwSta !== 4
            source: baseinfodatamodel.currentTheme ? "images/BaseInfo/LightTheme/Background.png" : "images/BaseInfo/DarkTheme/Background.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: background_DualScreen
            x: 0
            y: 0
            visible: centerviewdatamodel.Menu_SwSta === 3
            source: baseinfodatamodel.currentTheme ? "images/MenuView/DualScreen/LightTheme/Background_DualScreen.png" : "images/MenuView/DualScreen/DarkTheme/Background_DualScreen.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: background_LocalMusic
            x: 0
            y: 0
            visible: centerviewdatamodel.Menu_SwSta === 4
            source: baseinfodatamodel.currentTheme ? "images/MenuView/DualScreen/LightTheme/Background_LocalMusic.png" : "images/MenuView/DualScreen/DarkTheme/Background_LocalMusic.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: skyLine
            x: 0
            y: 0
            source: baseinfodatamodel.currentTheme ? "" : "images/MenuView/Adas/DarkTheme/SkyLine.png"
            fillMode: Image.PreserveAspectFit
        }

        Loader {
            id: centerView
            x: 518
            y: 204
            source: baseinfodatamodel.currentTheme ? "CenterView_Light.ui.qml" : "CenterView_Dark.ui.qml"
        }

        Loader {
            id: baseInfo
            source: baseinfodatamodel.currentTheme ? "BaseInfo_Light.ui.qml" : "BaseInfo_Dark.ui.qml"
        }

        Telltale {
            id: telltale
        }

        Loader {
            id: gauge
            source: baseinfodatamodel.currentTheme ? "Gauge_Light.ui.qml" : "Gauge_Dark.ui.qml"
        }

        Loader {
            id: warningPopup
            x: 670
            y: 184
            source: baseinfodatamodel.currentTheme ? "WarningPopup_Light.ui.qml" : "WarningPopup_Dark.ui.qml"
        }
    }

    Item {
        id: powerStatus_OFF
        visible: baseinfodatamodel.PowerSta === 2
        anchors.fill: parent

        Image {
            id: background_OFF
            x: 0
            y: 0
            source: baseinfodatamodel.currentTheme ? "images/BaseInfo/LightTheme/Background_OFF.png" : "images/BaseInfo/DarkTheme/Background_OFF.png"
            fillMode: Image.PreserveAspectFit
        }

        Loader {
            id: doorCover_OFF
            x: 780
            y: 144
            source: baseinfodatamodel.currentTheme ? "DoorCover_OFF_Light.ui.qml" : "DoorCover_OFF_Dark.ui.qml"
        }

        Telltale_OFF {
            id: telltale_OFF
        }

        Loader {
            id: warningPopup_OFF
            x: 670
            y: 184
            source: baseinfodatamodel.currentTheme ? "WarningPopup_OFF_Light.ui.qml" : "WarningPopup_OFF_Dark.ui.qml"
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/

