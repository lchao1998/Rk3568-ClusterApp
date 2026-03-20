

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
        source: "images/MenuView/SeatBelt/DarkTheme/Car.png"
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit

        Item {
            id: mainSeatBelt
            x: 97
            y: 120
            width: 39
            height: 43

            Image {
                id: seatBelt_Fastened
                source: "images/MenuView/SeatBelt/SeatBelt_Fastened.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: seatBelt_Unfastened
                visible: telltaledatamodel.DrvSeatbeltBucklestatus
                         && telltaledatamodel.DrvSeatOccSta
                source: "images/MenuView/SeatBelt/SeatBelt_Unfastened.png"
                fillMode: Image.PreserveAspectFit
            }
        }

        Item {
            id: passSeatBelt_FR
            x: 157
            y: 120
            width: 39
            height: 43
            Image {
                id: seatBelt_Fastened1
                source: "images/MenuView/SeatBelt/SeatBelt_Fastened.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: seatBelt_Unfastened1
                visible: telltaledatamodel.PAssSeatbeltBucklestatus
                         && telltaledatamodel.PassSeatOccSta
                source: "images/MenuView/SeatBelt/SeatBelt_Unfastened.png"
                fillMode: Image.PreserveAspectFit
            }
        }

        Item {
            id: passSeatBelt_RL
            x: 83
            y: 188
            width: 39
            height: 43
            Image {
                id: seatBelt_Fastened2
                source: "images/MenuView/SeatBelt/SeatBelt_Fastened.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: seatBelt_Unfastened2
                visible: centerviewdatamodel.SeatbeltBucklestatusRL
                         && centerviewdatamodel.RLSeatOccSta
                source: "images/MenuView/SeatBelt/SeatBelt_Unfastened.png"
                fillMode: Image.PreserveAspectFit
            }
        }

        Item {
            id: passSeatBelt_RM
            x: 127
            y: 188
            width: 39
            height: 43
            Image {
                id: seatBelt_Fastened3
                source: "images/MenuView/SeatBelt/SeatBelt_Fastened.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: seatBelt_Unfastened3
                visible: centerviewdatamodel.SeatbeltBucklestatusRM
                         && centerviewdatamodel.RMSeatOccSta
                source: "images/MenuView/SeatBelt/SeatBelt_Unfastened.png"
                fillMode: Image.PreserveAspectFit
            }
        }

        Item {
            id: passSeatBelt_RR
            x: 171
            y: 188
            width: 39
            height: 43
            Image {
                id: seatBelt_Fastened4
                source: "images/MenuView/SeatBelt/SeatBelt_Fastened.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: seatBelt_Unfastened4
                visible: centerviewdatamodel.SeatbeltBucklestatusRR
                         && centerviewdatamodel.RRSeatOccSta
                source: "images/MenuView/SeatBelt/SeatBelt_Unfastened.png"
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

