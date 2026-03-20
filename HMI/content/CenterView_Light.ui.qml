

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: item1
    width: 884
    height: 473

    Adas_Light {
        id: adas
        visible: centerviewdatamodel.Menu_SwSta === 0
    }

    TripComputer_Light {
        id: tripComputer
        visible: centerviewdatamodel.Menu_SwSta === 1
                 || centerviewdatamodel.Menu_SwSta === 2
    }

    Text {
        id: daulScreen_MapFailed
        visible: centerviewdatamodel.Menu_SwSta === 0xf0
        color: "#cb2f2f"
        text: qsTr("暂未获取地图信息，请稍后...")
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 30
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Text {
        id: daulScreen_MultimediaFailed
        visible: centerviewdatamodel.Menu_SwSta === 0xf1
        color: "#cb2f2f"
        text: qsTr("暂未获取多媒体信息，请稍后...")
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 30
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Text {
        id: daulScreen_ScreenFailed
        visible: centerviewdatamodel.Menu_SwSta === 0xf2
        color: "#cb2f2f"
        text: qsTr("投屏失败...")
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 30
        anchors.horizontalCenter: parent.horizontalCenter
    }

    DoorCover_Light {
        id: doorCover
        visible: centerviewdatamodel.currentStatus === 1
    }

    RadarAlarm_Light {
        id: radarAlarm
        visible: centerviewdatamodel.currentStatus === 2
    }

    SeatBelt_Light {
        id: seatBelt
        visible: centerviewdatamodel.currentStatus === 3
    }

    TirePressure_Light {
        id: tirePressure
        visible: centerviewdatamodel.currentStatus === 4
    }
}

/*##^##
Designer {
    D{i:0;height:473;width:884}
}
##^##*/

