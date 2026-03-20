

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
        id: laneline_Left
        y: 0
        anchors.left: parent.left
        source: "images/MenuView/Adas/DarkTheme/Laneline_Left.png"
        anchors.leftMargin: 0
        fillMode: Image.PreserveAspectFit

        Image {
            id: outline_Left
            y: 0
            anchors.left: parent.left
            source: "images/MenuView/Adas/DarkTheme/Outline_Left.png"
            anchors.leftMargin: 176
            fillMode: Image.PreserveAspectFit
        }
    }

    Image {
        id: laneline_Right
        x: 546
        y: 0
        anchors.right: parent.right
        source: "images/MenuView/Adas/DarkTheme/Laneline_Right.png"
        anchors.rightMargin: 0
        fillMode: Image.PreserveAspectFit

        Image {
            id: outline_Right
            x: -60
            y: 0
            anchors.right: parent.right
            source: "images/MenuView/Adas/DarkTheme/Outline_Right.png"
            anchors.rightMargin: 176
            fillMode: Image.PreserveAspectFit
        }
    }

    Image {
        id: carShadow
        anchors.top: car.bottom
        source: "images/MenuView/Adas/DarkTheme/CarShadow.png"
        anchors.horizontalCenterOffset: 0
        anchors.topMargin: -30
        anchors.horizontalCenter: car.horizontalCenter
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: car
        anchors.verticalCenter: parent.verticalCenter
        source: "images/MenuView/Adas/DarkTheme/Car.png"
        anchors.verticalCenterOffset: 30
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5;height:473;width:884}
}
##^##*/

