

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
    width: 1920
    height: 720

    Item {
        id: left_Dial
        width: 546
        height: 546
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.leftMargin: 0

        SpeedDial {
            id: speedDial
        }

        DigitalDisplay_Dark {
            id: speedDisplay
            x: 176
            anchors.right: parent.right
            anchors.top: parent.top
            number: gaugedatamodel.HU_DisvehicleSpeed
            anchors.rightMargin: 30
            anchors.topMargin: 70
        }

        Image {
            id: km_h
            anchors.top: speedDisplay.bottom
            source: "images/Gauge/km_h.png"
            anchors.topMargin: 20
            anchors.horizontalCenterOffset: 70
            anchors.horizontalCenter: parent.horizontalCenter
            fillMode: Image.PreserveAspectFit
        }
        InvertEffect {
            id: speedInvert
            anchors.top: speedDisplay.bottom
            anchors.horizontalCenter: speedDisplay.horizontalCenter
            m_target: speedDisplay
        }
    }

    Item {
        id: right_Dial
        width: 546
        height: 546
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 0
        anchors.bottomMargin: 0

        TachoDial {
            id: tachoDial
        }

        Item {
            id: oil
            visible: false
            anchors.fill: parent

            DigitalDisplay_Dark {
                id: tachoDisplay_Oil
                x: 30
                y: 70
                visible: true
                anchors.left: parent.left
                anchors.top: parent.top
                number: gaugedatamodel.revSpeed
                anchors.leftMargin: 30
                anchors.topMargin: 70
            }

            Image {
                id: x1000rpm
                x: 131
                y: 238
                anchors.top: tachoDisplay_Oil.bottom
                source: "images/Gauge/x1000rpm.png"
                anchors.topMargin: 20
                anchors.horizontalCenterOffset: -70
                anchors.horizontalCenter: parent.horizontalCenter
                fillMode: Image.PreserveAspectFit
            }

            InvertEffect {
                id: tachoInvert
                x: 0
                y: 0
                anchors.top: tachoDisplay_Oil.bottom
                anchors.horizontalCenter: tachoDisplay_Oil.horizontalCenter
                m_target: tachoDisplay_Oil
            }
        }

        Item {
            id: electric
            anchors.fill: parent

            DigitalDisplay_Dark {
                id: tachoDisplay_Electric
                x: 30
                y: 70
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.leftMargin: 30
                anchors.topMargin: 70
                number: gaugedatamodel.MotorPower
            }

            Image {
                id: kw
                x: 183
                y: 238
                anchors.top: tachoDisplay_Electric.bottom
                source: "images/Gauge/kw.png"
                anchors.horizontalCenterOffset: -70
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: 20
                fillMode: Image.PreserveAspectFit
            }

            InvertEffect {
                id: tachoInvert1
                x: 0
                y: 0
                anchors.top: tachoDisplay_Electric.bottom
                anchors.horizontalCenter: tachoDisplay_Electric.horizontalCenter
                m_target: tachoDisplay_Electric
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5;height:720;width:1920}
}
##^##*/

