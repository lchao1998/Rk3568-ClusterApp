import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: digitalDisplay
    width: 320
    height: 148
    property string number: "0"
    state: "base state"


    Row {
        id: digits
        spacing: 7
        anchors.horizontalCenter: parent.horizontalCenter

        Image {
            id: _2
            width: 98
            visible: false
            source: "images/Gauge/LightTheme/number/0.png"
            asynchronous: true
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: _1
            width: 98
            visible: false
            source: "images/Gauge/LightTheme/number/0.png"
            asynchronous: true
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: _0
            width: 98
            source: "images/Gauge/LightTheme/number/0.png"
            asynchronous: true
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: _p
            visible: false
            anchors.bottom: parent.bottom
            source: "images/Gauge/LightTheme/number/point.png"
            asynchronous: true
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: _p1
            width: 98
            visible: false
            source: "images/Gauge/LightTheme/number/0.png"
            asynchronous: true
            fillMode: Image.PreserveAspectFit
        }
    }

    Connections {
        target: digitalDisplay
        onNumberChanged: {
            var str = number.toString()
            if (str.indexOf(".") === -1) {
                if (str.length === 3) {
                    _2.source = "images/Gauge/LightTheme/number/" + str[0] + ".png"
                    _1.source = "images/Gauge/LightTheme/number/" + str[1] + ".png"
                    _0.source = "images/Gauge/LightTheme/number/" + str[2] + ".png"
                    digitalDisplay.state = "three_digits"
                } else if (str.length === 2) {
                    _1.source = "images/Gauge/LightTheme/number/" + str[0] + ".png"
                    _0.source = "images/Gauge/LightTheme/number/" + str[1] + ".png"
                    digitalDisplay.state = "double_digits"
                } else if (str.length === 1) {
                    _0.source = "images/Gauge/LightTheme/number/" + str[0] + ".png"
                    digitalDisplay.state = "base state"
                }
            } else {
                _0.source = "images/Gauge/LightTheme/number/" + str[0] + ".png"
                _p1.source = "images/Gauge/LightTheme/number/" + str[2] + ".png"
                digitalDisplay.state = "point_digits"
            }
        }
    }

    Component.onCompleted:
    {
        var str = number.toString()
        if (str.indexOf(".") === -1) {
            if (str.length === 3) {
                _2.source = "images/Gauge/LightTheme/number/" + str[0] + ".png"
                _1.source = "images/Gauge/LightTheme/number/" + str[1] + ".png"
                _0.source = "images/Gauge/LightTheme/number/" + str[2] + ".png"
                digitalDisplay.state = "three_digits"
            } else if (str.length === 2) {
                _1.source = "images/Gauge/LightTheme/number/" + str[0] + ".png"
                _0.source = "images/Gauge/LightTheme/number/" + str[1] + ".png"
                digitalDisplay.state = "double_digits"
            } else if (str.length === 1) {
                _0.source = "images/Gauge/LightTheme/number/" + str[0] + ".png"
                digitalDisplay.state = "base state"
            }
        } else {
            _0.source = "images/Gauge/LightTheme/number/" + str[0] + ".png"
            _p1.source = "images/Gauge/LightTheme/number/" + str[2] + ".png"
            digitalDisplay.state = "point_digits"
        }

    }

    states: [
        State {
            name: "double_digits"

            PropertyChanges {
                target: _1
                visible: true
            }
        },
        State {
            name: "three_digits"

            PropertyChanges {
                target: _1
                visible: true
            }

            PropertyChanges {
                target: _2
                visible: true
            }
        },
        State {
            name: "point_digits"

            PropertyChanges {
                target: _p
                visible: true
            }

            PropertyChanges {
                target: _p1
                visible: true
            }
        }
    ]
}

/*##^##
Designer {
    D{i:0;height:148;width:320}
}
##^##*/
