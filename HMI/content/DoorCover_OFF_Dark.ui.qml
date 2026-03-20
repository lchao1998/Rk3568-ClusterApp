

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
    width: 360
    height: 432

    Image {
        id: car
        anchors.verticalCenter: parent.verticalCenter
        source: "images/MenuView/DoorCover_OFF/DarkTheme/Car.png"
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit

        Item {
            id: close
            anchors.fill: parent

            Image {
                id: leftRear_Close
                x: 0
                y: 0
                source: "images/MenuView/DoorCover_OFF/DarkTheme/Close_LR.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: leftFront_Close
                x: 0
                y: 0
                source: "images/MenuView/DoorCover_OFF/DarkTheme/Close_LF.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: rightFront_Close
                x: 0
                y: 0
                source: "images/MenuView/DoorCover_OFF/DarkTheme/Close_RF.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: rightRear_Close
                x: 0
                y: 0
                source: "images/MenuView/DoorCover_OFF/DarkTheme/Close_RR.png"
                fillMode: Image.PreserveAspectFit
            }
        }
        Item {
            id: open
            anchors.fill: parent

            Image {
                id: hood
                x: 0
                y: 0
                visible: telltaledatamodel.HoodSta
                source: "images/MenuView/DoorCover_OFF/Hood.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: back
                x: 0
                y: 0
                visible: telltaledatamodel.TrunkSta
                source: "images/MenuView/DoorCover_OFF/Back.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: leftFront_Open
                x: 0
                y: 0
                visible: telltaledatamodel.doorajarFL
                source: "images/MenuView/DoorCover_OFF/Open_LF.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: leftRear_Open
                x: 0
                y: 0
                visible: telltaledatamodel.doorajarRL
                source: "images/MenuView/DoorCover_OFF/Open_LR.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: rightFront_Open
                x: 0
                y: 0
                visible: telltaledatamodel.doorajarFR
                source: "images/MenuView/DoorCover_OFF/Open_RF.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: rightRear_Open
                x: 0
                y: 0
                visible: telltaledatamodel.doorajarRR
                source: "images/MenuView/DoorCover_OFF/Open_RR.png"
                fillMode: Image.PreserveAspectFit
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.33;height:432;width:360}
}
##^##*/

