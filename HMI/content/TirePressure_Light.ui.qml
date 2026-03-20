

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
        source: "images/MenuView/TirePressure/LightTheme/Car.png"
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit

        Item {
            id: tirePressure_LF
            anchors.fill: parent

            Image {
                id: normal_LF
                x: 0
                y: 0
                source: "images/MenuView/TirePressure/LightTheme/Normal_LF.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: abnormal_LF
                x: 0
                y: 0
                visible: telltaledatamodel.TPMSPressureStaFL > 1
                source: "images/MenuView/TirePressure/LightTheme/Abnormal_LF.png"
                fillMode: Image.PreserveAspectFit
            }
        }

        Item {
            id: tirePressure_RF
            anchors.fill: parent

            Image {
                id: normal_RF
                x: 0
                y: 0
                source: "images/MenuView/TirePressure/LightTheme/Normal_RF.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: abnormal_RF
                x: 0
                y: 0
                visible: telltaledatamodel.TPMSPressureStaFR > 1
                source: "images/MenuView/TirePressure/LightTheme/Abnormal_RF.png"
                fillMode: Image.PreserveAspectFit
            }
        }

        Item {
            id: tirePressure_LR
            anchors.fill: parent

            Image {
                id: normal_LR
                x: 0
                y: 0
                source: "images/MenuView/TirePressure/LightTheme/Normal_LR.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: abnormal_LR
                x: 0
                y: 0
                visible: telltaledatamodel.TPMSPressureStaRL > 1
                source: "images/MenuView/TirePressure/LightTheme/Abnormal_LR.png"
                fillMode: Image.PreserveAspectFit
            }
        }

        Item {
            id: passSeatBelt_RR
            anchors.fill: parent

            Image {
                id: normal_RR
                x: 0
                y: 0
                source: "images/MenuView/TirePressure/LightTheme/Normal_RR.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: abnormal_RR
                x: 0
                y: 0
                visible: telltaledatamodel.TPMSPressureStaRR > 1
                source: "images/MenuView/TirePressure/LightTheme/Abnormal_RR.png"
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

