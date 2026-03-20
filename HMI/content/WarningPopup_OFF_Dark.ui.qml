

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
    width: 580
    height: 130

    Item {
        id: textAlarm_B
        anchors.fill: parent

        Image {
            id: pEPSWarnSta
            visible: warningpopupdatamodel.PEPSWarnSta_Pop === true
            source: "images/WarningPopup/DarkTheme/Yellow_Bg.png"
            Image {
                id: pePSWarnSta
                y: 25
                width: 80
                height: 80
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/PEPS.png"
                fillMode: Image.PreserveAspectFit
                anchors.leftMargin: 70
                anchors.verticalCenterOffset: 0
            }

            Text {
                id: text28
                y: 45
                color: "#ff9600"
                text: qsTr("PEPS系统故障")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }
    }
}

/*##^##
Designer {
    D{i:0;height:130;width:580}
}
##^##*/

