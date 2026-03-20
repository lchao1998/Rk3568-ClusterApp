

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

    Image {
        id: car
        anchors.verticalCenter: parent.verticalCenter
        source: "images/MenuView/DoorCover/LightTheme/Car.png"
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit

        Item {
            id: close
            anchors.fill: parent

            Image {
                id: leftRear_Close
                x: 0
                y: 0
                source: "images/MenuView/DoorCover/LightTheme/LeftRear_Close.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: leftFront_Close
                x: 0
                y: 0
                source: "images/MenuView/DoorCover/LightTheme/LeftFront_Close.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: rightFront_Close
                x: 0
                y: 0
                source: "images/MenuView/DoorCover/LightTheme/RightFront_Close.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: rightRear_Close
                x: 0
                y: 0
                source: "images/MenuView/DoorCover/LightTheme/RightRear_Close.png"
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
                source: "images/MenuView/DoorCover/Hood.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: back
                x: 0
                y: 0
                visible: telltaledatamodel.TrunkSta
                source: "images/MenuView/DoorCover/Back.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: leftFront_Open
                x: 0
                y: 0
                visible: telltaledatamodel.doorajarFL
                source: "images/MenuView/DoorCover/LeftFront_Open.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: leftRear_Open
                x: 0
                y: 0
                visible: telltaledatamodel.doorajarRL
                source: "images/MenuView/DoorCover/LeftRear_Open.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: rightFront_Open
                x: 0
                y: 0
                visible: telltaledatamodel.doorajarFR
                source: "images/MenuView/DoorCover/RightFront_Open.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: rightRear_Open
                x: 0
                y: 0
                visible: telltaledatamodel.doorajarRR
                source: "images/MenuView/DoorCover/RightRear_Open.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: chargingAndOil_Port
                x: 0
                y: 0
                visible: telltaledatamodel.FueldoorSta
                         || telltaledatamodel.ChargeSta
                source: "images/MenuView/DoorCover/ChargingAndOil_Port.png"
                fillMode: Image.PreserveAspectFit
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;height:473;width:884}
}
##^##*/

