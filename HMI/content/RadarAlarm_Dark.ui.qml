

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
        source: "images/MenuView/RadarAlarm/DarkTheme/Car.png"
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit

        Item {
            id: radarAlarm_RL
            anchors.fill: parent

            Image {
                id: _30_RL
                x: 0
                y: 0
                visible: centerviewdatamodel.PASDistanceRL === 1
                source: "images/MenuView/RadarAlarm/0-30cm/1.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: _60_RL
                x: 0
                y: 0
                visible: centerviewdatamodel.PASDistanceRL > 1
                         && centerviewdatamodel.PASDistanceRL <= 4

                source: "images/MenuView/RadarAlarm/30-60cm/1.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: _90_RL
                x: 0
                y: 0
                visible: centerviewdatamodel.PASDistanceRL > 4
                         && centerviewdatamodel.PASDistanceRL <= 7
                source: "images/MenuView/RadarAlarm/60-90cm/1.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: _150_RL
                x: 0
                y: 0
                visible: centerviewdatamodel.PASDistanceRL > 7
                         && centerviewdatamodel.PASDistanceRL <= 10
                source: "images/MenuView/RadarAlarm/90-150cm/1.png"
                fillMode: Image.PreserveAspectFit
            }
        }

        Item {
            id: radarAlarm_RML
            anchors.fill: parent
            Image {
                id: _30_RML
                x: 0
                y: 0
                visible: centerviewdatamodel.PASDistanceRML === 1
                source: "images/MenuView/RadarAlarm/0-30cm/2.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: _60_RML
                x: 0
                y: 0
                visible: centerviewdatamodel.PASDistanceRML > 1
                         && centerviewdatamodel.PASDistanceRML <= 4
                source: "images/MenuView/RadarAlarm/30-60cm/2.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: _90_RML
                x: 0
                y: 0
                visible: centerviewdatamodel.PASDistanceRML > 4
                         && centerviewdatamodel.PASDistanceRML <= 7
                source: "images/MenuView/RadarAlarm/60-90cm/2.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: _150_RML
                x: 0
                y: 0
                visible: centerviewdatamodel.PASDistanceRML > 7
                         && centerviewdatamodel.PASDistanceRML <= 10
                source: "images/MenuView/RadarAlarm/90-150cm/2.png"
                fillMode: Image.PreserveAspectFit
            }
        }

        Item {
            id: radarAlarm_RMR
            anchors.fill: parent
            Image {
                id: _30_RMR
                x: 0
                y: 0
                visible: centerviewdatamodel.PASDistanceRMR === 1
                source: "images/MenuView/RadarAlarm/0-30cm/3.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: _60_RMR
                x: 0
                y: 0
                visible: centerviewdatamodel.PASDistanceRMR > 1
                         && centerviewdatamodel.PASDistanceRMR <= 4
                source: "images/MenuView/RadarAlarm/30-60cm/3.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: _90_RMR
                x: 0
                y: 0
                visible: centerviewdatamodel.PASDistanceRMR > 4
                         && centerviewdatamodel.PASDistanceRMR <= 7
                source: "images/MenuView/RadarAlarm/60-90cm/3.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: _150_RMR
                x: 0
                y: 0
                visible: centerviewdatamodel.PASDistanceRMR > 7
                         && centerviewdatamodel.PASDistanceRMR <= 10
                source: "images/MenuView/RadarAlarm/90-150cm/3.png"
                fillMode: Image.PreserveAspectFit
            }
        }

        Item {
            id: radarAlarm_RR
            anchors.fill: parent
            Image {
                id: _30_RR
                x: 0
                y: 0
                visible: centerviewdatamodel.PASDistanceRR === 1
                source: "images/MenuView/RadarAlarm/0-30cm/4.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: _60_RR
                x: 0
                y: 0
                visible: centerviewdatamodel.PASDistanceRR > 1
                         && centerviewdatamodel.PASDistanceRR <= 4
                source: "images/MenuView/RadarAlarm/30-60cm/4.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: _90_RR
                x: 0
                y: 0
                visible: centerviewdatamodel.PASDistanceRR > 4
                         && centerviewdatamodel.PASDistanceRR <= 7
                source: "images/MenuView/RadarAlarm/60-90cm/4.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: _150_RR
                x: 0
                y: 0
                visible: centerviewdatamodel.PASDistanceRR > 7
                         && centerviewdatamodel.PASDistanceRR <= 10
                source: "images/MenuView/RadarAlarm/90-150cm/4.png"
                fillMode: Image.PreserveAspectFit
            }
        }

        Item {
            id: radarFault
            anchors.fill: parent

            Image {
                id: _1
                x: 0
                y: 0
                visible: centerviewdatamodel.PASSta_RL === 2
                source: "images/MenuView/RadarAlarm/RadarFault/1.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: _2
                x: 0
                y: 0
                visible: centerviewdatamodel.PASSta__RML === 2
                source: "images/MenuView/RadarAlarm/RadarFault/2.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: _3
                x: 0
                y: 0
                visible: centerviewdatamodel.PASSta__RMR === 2
                source: "images/MenuView/RadarAlarm/RadarFault/3.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: _4
                x: 0
                y: 0
                visible: centerviewdatamodel.PASSta__RR === 2
                source: "images/MenuView/RadarAlarm/RadarFault/4.png"
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

