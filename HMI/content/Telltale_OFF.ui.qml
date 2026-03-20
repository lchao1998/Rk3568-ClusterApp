

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

Item {
    id: item1
    width: 1920
    height: 720

    Image {
        id: highBeamLamp
        x: 413
        y: 34
        width: 60
        height: 60
        source: telltaledatamodel.Flashbeam ? "images/TT/HighBeamLamp.png" : ""
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: leftTurnLight
        x: 635
        y: 24
        width: 80
        height: 80
        source: telltaledatamodel.turnlamp === 3 ? "images/TT/LeftTurnLight.png" : ""
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: rightTurnLight
        x: 1205
        y: 25
        width: 80
        height: 80
        source: telltaledatamodel.turnlamp === 3 ? "images/TT/RightTurnLight.png" : ""
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: pEPS
        x: 413
        y: 114
        width: 60
        height: 60
        source: telltaledatamodel.PEPSWarnSta ? "images/TT/PEPS.png" : ""
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: open_door
        x: 1817
        y: 114
        width: 60
        height: 60
        source: telltaledatamodel.doorajarFL || telltaledatamodel.doorajarFR
                || telltaledatamodel.doorajarRL || telltaledatamodel.doorajarRR
                || telltaledatamodel.HoodSta
                || telltaledatamodel.TrunkSta ? "images/TT/Open_door.png" : ""
        fillMode: Image.PreserveAspectFit
    }

    Item {
        id: item_Electric
        x: 1225
        y: 114
        width: 60
        height: 60
        visible: true

        Image {
            id: charging_connection
            width: 60
            height: 60
            source: telltaledatamodel.InletConnctSta ? "images/TT/Charging_connection.png" : ""
            fillMode: Image.PreserveAspectFit
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5;height:720;width:1920}
}
##^##*/

