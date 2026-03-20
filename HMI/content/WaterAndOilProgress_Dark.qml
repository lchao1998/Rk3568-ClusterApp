import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: item1
    width: 208
    height: 18
    property int value: 0

    Image {
        id: waterAndOil_Bg
        anchors.top: parent.top
        source: "images/BaseInfo/DarkTheme/WaterAndOil_Bg.png"
        clip: true
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 0
        fillMode: Image.PreserveAspectFit

        Image {
            id: waterAndOil_Fg
            x: value
            y: 0
            anchors.top: parent.top
            source: "images/BaseInfo/DarkTheme/WaterAndOil_Fg.png"
            anchors.topMargin: 0
            fillMode: Image.PreserveAspectFit
        }
    }

    Image {
        id: scale1
        x: 0
        y: 0
        anchors.bottom: parent.bottom
        source: "images/BaseInfo/DarkTheme/scale.png"
        anchors.bottomMargin: 0
        fillMode: Image.PreserveAspectFit
    }
}

/*##^##
Designer {
    D{i:0;height:18;width:208}
}
##^##*/
