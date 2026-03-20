

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
    width: 884
    height: 473

    StackLayout {
        id: stackLayout_Oil
        width: 500
        height: 285
        visible: false
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        Item {
            id: page1
            width: 500
            height: 285

            Rectangle {
                id: rectangle
                x: 0
                width: 240
                height: 136
                radius: 8
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.horizontalCenterOffset: -130
                anchors.horizontalCenter: parent.horizontalCenter
                gradient: Gradient {
                    orientation: Gradient.Vertical
                    GradientStop {
                        position: 0
                        color: "#f1f9ff"
                    }

                    GradientStop {
                        position: 1
                        color: "#facee4f7"
                    }
                }

                Text {
                    id: text1
                    x: 20
                    y: 20
                    color: "#2f3a4a"
                    text: qsTr("单次行驶里程")
                    font.pixelSize: 24
                    font.family: "Source Han Sans CN Normal"
                }

                Row {
                    id: row
                    x: 20
                    y: 60
                    width: 200
                    height: 36
                    spacing: 8

                    Text {
                        id: value
                        color: "#2f3a4a"
                        text: baseinfodatamodel.HU_TripOdometer
                        font.pixelSize: 32
                        font.family: "Source Han Sans CN Normal"
                    }

                    Text {
                        id: unit
                        color: "#2f3a4a"
                        text: qsTr("km")
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 24
                        font.family: "Source Han Sans CN Normal"
                    }
                }
            }

            Rectangle {
                id: rectangle1
                x: 260
                width: 240
                height: 136
                radius: 8
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.horizontalCenterOffset: 130
                anchors.horizontalCenter: parent.horizontalCenter
                gradient: Gradient {
                    orientation: Gradient.Vertical
                    GradientStop {
                        position: 0
                        color: "#f1f9ff"
                    }

                    GradientStop {
                        position: 1
                        color: "#facee4f7"
                    }
                }

                Text {
                    id: text2
                    x: 20
                    y: 20
                    color: "#2f3a4a"
                    text: qsTr("平均车速")
                    font.pixelSize: 24
                    font.family: "Source Han Sans CN Normal"
                }

                Row {
                    id: row1
                    x: 20
                    y: 60
                    width: 200
                    height: 36
                    spacing: 8
                    Text {
                        id: value1
                        color: "#2f3a4a"
                        text: centerviewdatamodel.HU_AvgVehicleSpeed
                        font.pixelSize: 32
                        font.family: "Source Han Sans CN Normal"
                    }

                    Text {
                        id: unit1
                        color: "#2f3a4a"
                        text: qsTr("km/h")
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 24
                        font.family: "Source Han Sans CN Normal"
                    }
                }
            }

            Rectangle {
                id: rectangle2
                x: 0
                y: 180
                width: 240
                height: 136
                radius: 8
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.horizontalCenterOffset: -130
                anchors.horizontalCenter: parent.horizontalCenter
                gradient: Gradient {
                    orientation: Gradient.Vertical
                    GradientStop {
                        position: 0
                        color: "#f1f9ff"
                    }

                    GradientStop {
                        position: 1
                        color: "#facee4f7"
                    }
                }

                Text {
                    id: text3
                    x: 20
                    y: 20
                    color: "#2f3a4a"
                    text: qsTr("百公里平均油耗")
                    font.pixelSize: 24
                    font.family: "Source Han Sans CN Normal"
                }

                Row {
                    id: row2
                    x: 20
                    y: 60
                    width: 200
                    height: 36
                    spacing: 8
                    Text {
                        id: value2
                        color: "#2f3a4a"
                        text: qsTr("--")
                        font.pixelSize: 32
                        font.family: "Source Han Sans CN Normal"
                    }

                    Text {
                        id: unit2
                        color: "#2f3a4a"
                        text: qsTr("L/100km")
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 24
                        font.family: "Source Han Sans CN Normal"
                    }
                }
            }

            Rectangle {
                id: rectangle3
                x: 260
                y: 180
                width: 240
                height: 136
                radius: 8
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.horizontalCenterOffset: 130
                anchors.horizontalCenter: parent.horizontalCenter
                gradient: Gradient {
                    orientation: Gradient.Vertical
                    GradientStop {
                        position: 0
                        color: "#f1f9ff"
                    }

                    GradientStop {
                        position: 1
                        color: "#facee4f7"
                    }
                }

                Text {
                    id: text4
                    x: 20
                    y: 20
                    color: "#2f3a4a"
                    text: qsTr("加油后平均油耗")
                    font.pixelSize: 24
                    font.family: "Source Han Sans CN Normal"
                }

                Row {
                    id: row3
                    x: 20
                    y: 60
                    width: 200
                    height: 36
                    spacing: 8
                    Text {
                        id: value3
                        color: "#2f3a4a"
                        text: qsTr("--")
                        font.pixelSize: 32
                        font.family: "Source Han Sans CN Normal"
                    }

                    Text {
                        id: unit3
                        color: "#2f3a4a"
                        text: qsTr("L/100km")
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 24
                        font.family: "Source Han Sans CN Normal"
                    }
                }
            }
        }

        Item {
            id: page2
            width: 500
            height: 285
            Rectangle {
                id: rectangle4
                x: 0
                width: 240
                height: 136
                radius: 8
                anchors.top: parent.top
                anchors.horizontalCenterOffset: -130
                anchors.topMargin: 0
                anchors.horizontalCenter: parent.horizontalCenter
                Text {
                    id: text5
                    x: 20
                    y: 20
                    color: "#2f3a4a"
                    text: qsTr("小计里程A")
                    font.pixelSize: 24
                    font.family: "Source Han Sans CN Normal"
                }

                Row {
                    id: row4
                    x: 20
                    y: 60
                    width: 200
                    height: 36
                    Text {
                        id: value4
                        color: "#2f3a4a"
                        text: baseinfodatamodel.HU_TripAOdometer
                        font.pixelSize: 32
                        font.family: "Source Han Sans CN Normal"
                    }

                    Text {
                        id: unit4
                        color: "#2f3a4a"
                        text: qsTr("km")
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 24
                        font.family: "Source Han Sans CN Normal"
                    }
                    spacing: 8
                }
                gradient: Gradient {
                    orientation: Gradient.Vertical
                    GradientStop {
                        position: 0
                        color: "#f1f9ff"
                    }

                    GradientStop {
                        position: 1
                        color: "#facee4f7"
                    }
                }
            }

            Rectangle {
                id: rectangle5
                x: 260
                width: 240
                height: 136
                radius: 8
                anchors.top: parent.top
                anchors.horizontalCenterOffset: 130
                anchors.topMargin: 0
                anchors.horizontalCenter: parent.horizontalCenter
                Text {
                    id: text6
                    x: 20
                    y: 20
                    color: "#2f3a4a"
                    text: qsTr("小计里程B")
                    font.pixelSize: 24
                    font.family: "Source Han Sans CN Normal"
                }

                Row {
                    id: row5
                    x: 20
                    y: 60
                    width: 200
                    height: 36
                    Text {
                        id: value5
                        color: "#2f3a4a"
                        text: baseinfodatamodel.HU_TripBOdometer
                        font.pixelSize: 32
                        font.family: "Source Han Sans CN Normal"
                    }

                    Text {
                        id: unit5
                        color: "#2f3a4a"
                        text: qsTr("km")
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 24
                        font.family: "Source Han Sans CN Normal"
                    }
                    spacing: 8
                }
                gradient: Gradient {
                    orientation: Gradient.Vertical
                    GradientStop {
                        position: 0
                        color: "#f1f9ff"
                    }

                    GradientStop {
                        position: 1
                        color: "#facee4f7"
                    }
                }
            }

            Rectangle {
                id: rectangle6
                x: 0
                y: 180
                width: 240
                height: 136
                radius: 8
                anchors.bottom: parent.bottom
                anchors.horizontalCenterOffset: -130
                anchors.horizontalCenter: parent.horizontalCenter
                Text {
                    id: text7
                    x: 20
                    y: 20
                    color: "#2f3a4a"
                    text: qsTr("瞬时油耗")
                    font.pixelSize: 24
                    font.family: "Source Han Sans CN Normal"
                }

                Row {
                    id: row6
                    x: 20
                    y: 60
                    width: 200
                    height: 36
                    Text {
                        id: value6
                        color: "#2f3a4a"
                        text: qsTr("--")
                        font.pixelSize: 32
                        font.family: "Source Han Sans CN Normal"
                    }

                    Text {
                        id: unit6
                        color: "#2f3a4a"
                        text: qsTr("L/100km")
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 24
                        font.family: "Source Han Sans CN Normal"
                    }
                    spacing: 8
                }
                anchors.bottomMargin: 0
                gradient: Gradient {
                    orientation: Gradient.Vertical
                    GradientStop {
                        position: 0
                        color: "#f1f9ff"
                    }

                    GradientStop {
                        position: 1
                        color: "#facee4f7"
                    }
                }
            }
        }
    }

    StackLayout {
        id: stackLayout_Electric
        width: 500
        height: 285
        visible: true
        anchors.verticalCenter: parent.verticalCenter
        currentIndex: centerviewdatamodel.Menu_SwSta - 1
        anchors.horizontalCenter: parent.horizontalCenter
        Item {
            id: page3
            width: 500
            height: 285
            Rectangle {
                id: rectangle7
                x: 0
                width: 240
                height: 136
                radius: 8
                anchors.top: parent.top
                anchors.horizontalCenterOffset: -130
                anchors.topMargin: 0
                anchors.horizontalCenter: parent.horizontalCenter
                Text {
                    id: text8
                    x: 20
                    y: 20
                    color: "#2f3a4a"
                    text: qsTr("单次行驶里程")
                    font.pixelSize: 24
                    font.family: "Source Han Sans CN Normal"
                }

                Row {
                    id: row7
                    x: 20
                    y: 60
                    width: 200
                    height: 36
                    Text {
                        id: value7
                        color: "#2f3a4a"
                        text: baseinfodatamodel.HU_TripOdometer
                        font.pixelSize: 32
                        font.family: "Source Han Sans CN Normal"
                    }

                    Text {
                        id: unit7
                        color: "#2f3a4a"
                        text: qsTr("km")
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 24
                        font.family: "Source Han Sans CN Normal"
                    }
                    spacing: 8
                }
                gradient: Gradient {
                    orientation: Gradient.Vertical
                    GradientStop {
                        position: 0
                        color: "#f1f9ff"
                    }

                    GradientStop {
                        position: 1
                        color: "#facee4f7"
                    }
                }
            }

            Rectangle {
                id: rectangle8
                x: 260
                width: 240
                height: 136
                radius: 8
                anchors.top: parent.top
                anchors.horizontalCenterOffset: 130
                anchors.topMargin: 0
                anchors.horizontalCenter: parent.horizontalCenter
                Text {
                    id: text9
                    x: 20
                    y: 20
                    color: "#2f3a4a"
                    text: qsTr("平均车速")
                    font.pixelSize: 24
                    font.family: "Source Han Sans CN Normal"
                }

                Row {
                    id: row8
                    x: 20
                    y: 60
                    width: 200
                    height: 36
                    Text {
                        id: value8
                        color: "#2f3a4a"
                        text: centerviewdatamodel.HU_AvgVehicleSpeed
                        font.pixelSize: 32
                        font.family: "Source Han Sans CN Normal"
                    }

                    Text {
                        id: unit8
                        color: "#2f3a4a"
                        text: qsTr("km/h")
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 24
                        font.family: "Source Han Sans CN Normal"
                    }
                    spacing: 8
                }
                gradient: Gradient {
                    orientation: Gradient.Vertical
                    GradientStop {
                        position: 0
                        color: "#f1f9ff"
                    }

                    GradientStop {
                        position: 1
                        color: "#facee4f7"
                    }
                }
            }

            Rectangle {
                id: rectangle9
                x: 0
                y: 180
                width: 240
                height: 136
                radius: 8
                anchors.bottom: parent.bottom
                anchors.horizontalCenterOffset: -130
                anchors.horizontalCenter: parent.horizontalCenter
                Text {
                    id: text10
                    x: 20
                    y: 20
                    color: "#2f3a4a"
                    text: qsTr("平均电耗")
                    font.pixelSize: 24
                    font.family: "Source Han Sans CN Normal"
                }

                Row {
                    id: row9
                    x: 20
                    y: 60
                    width: 200
                    height: 36
                    Text {
                        id: value9
                        color: "#2f3a4a"
                        text: qsTr("--")
                        font.pixelSize: 32
                        font.bold: false
                        font.family: "Source Han Sans CN Normal"
                    }

                    Text {
                        id: unit9
                        color: "#2f3a4a"
                        text: qsTr("kwh/100km")
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 24
                        font.family: "Source Han Sans CN Normal"
                    }
                    spacing: 8
                }
                anchors.bottomMargin: 0
                gradient: Gradient {
                    orientation: Gradient.Vertical
                    GradientStop {
                        position: 0
                        color: "#f1f9ff"
                    }

                    GradientStop {
                        position: 1
                        color: "#facee4f7"
                    }
                }
            }

            Rectangle {
                id: rectangle10
                x: 260
                y: 180
                width: 240
                height: 136
                radius: 8
                anchors.bottom: parent.bottom
                anchors.horizontalCenterOffset: 130
                anchors.horizontalCenter: parent.horizontalCenter
                Text {
                    id: text11
                    x: 20
                    y: 20
                    color: "#2f3a4a"
                    text: qsTr("充电后平均电耗")
                    font.pixelSize: 24
                    font.family: "Source Han Sans CN Normal"
                }

                Row {
                    id: row10
                    x: 20
                    y: 60
                    width: 200
                    height: 36
                    Text {
                        id: value10
                        color: "#2f3a4a"
                        text: qsTr("--")
                        font.pixelSize: 32
                        font.family: "Source Han Sans CN Normal"
                    }

                    Text {
                        id: unit10
                        color: "#2f3a4a"
                        text: qsTr("kwh/100km")
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 24
                        font.family: "Source Han Sans CN Normal"
                    }
                    spacing: 8
                }
                anchors.bottomMargin: 0
                gradient: Gradient {
                    orientation: Gradient.Vertical
                    GradientStop {
                        position: 0
                        color: "#f1f9ff"
                    }

                    GradientStop {
                        position: 1
                        color: "#facee4f7"
                    }
                }
            }
        }

        Item {
            id: page4
            width: 500
            height: 285
            Rectangle {
                id: rectangle11
                x: 0
                width: 240
                height: 136
                radius: 8
                anchors.top: parent.top
                anchors.horizontalCenterOffset: -130
                anchors.topMargin: 0
                anchors.horizontalCenter: parent.horizontalCenter
                Text {
                    id: text12
                    x: 20
                    y: 20
                    color: "#2f3a4a"
                    text: qsTr("小计里程A")
                    font.pixelSize: 24
                    font.family: "Source Han Sans CN Normal"
                }

                Row {
                    id: row11
                    x: 20
                    y: 60
                    width: 200
                    height: 36
                    Text {
                        id: value11
                        color: "#2f3a4a"
                        text: (baseinfodatamodel.HU_TripAOdometer).toFixed(2)
                        font.pixelSize: 32
                        font.family: "Source Han Sans CN Normal"
                    }

                    Text {
                        id: unit11
                        color: "#2f3a4a"
                        text: qsTr("km")
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 24
                        font.family: "Source Han Sans CN Normal"
                    }
                    spacing: 8
                }
                gradient: Gradient {
                    orientation: Gradient.Vertical
                    GradientStop {
                        position: 0
                        color: "#f1f9ff"
                    }

                    GradientStop {
                        position: 1
                        color: "#facee4f7"
                    }
                }
            }

            Rectangle {
                id: rectangle12
                x: 260
                width: 240
                height: 136
                radius: 8
                anchors.top: parent.top
                anchors.horizontalCenterOffset: 130
                anchors.topMargin: 0
                anchors.horizontalCenter: parent.horizontalCenter
                Text {
                    id: text13
                    x: 20
                    y: 20
                    color: "#2f3a4a"
                    text: qsTr("小计里程B")
                    font.pixelSize: 24
                    font.family: "Source Han Sans CN Normal"
                }

                Row {
                    id: row12
                    x: 20
                    y: 60
                    width: 200
                    height: 36
                    Text {
                        id: value12
                        color: "#2f3a4a"
                        text: baseinfodatamodel.HU_TripBOdometer
                        font.pixelSize: 32
                        font.family: "Source Han Sans CN Normal"
                    }

                    Text {
                        id: unit12
                        color: "#2f3a4a"
                        text: qsTr("km")
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 24
                        font.family: "Source Han Sans CN Normal"
                    }
                    spacing: 8
                }
                gradient: Gradient {
                    orientation: Gradient.Vertical
                    GradientStop {
                        position: 0
                        color: "#f1f9ff"
                    }

                    GradientStop {
                        position: 1
                        color: "#facee4f7"
                    }
                }
            }

            Rectangle {
                id: rectangle13
                x: 0
                y: 180
                width: 240
                height: 136
                radius: 8
                anchors.bottom: parent.bottom
                anchors.horizontalCenterOffset: -130
                anchors.horizontalCenter: parent.horizontalCenter
                Text {
                    id: text14
                    x: 20
                    y: 20
                    color: "#2f3a4a"
                    text: qsTr("动力电池电压")
                    font.pixelSize: 24
                    font.family: "Source Han Sans CN Normal"
                }

                Row {
                    id: row13
                    x: 20
                    y: 60
                    width: 200
                    height: 36
                    Text {
                        id: value13
                        color: "#2f3a4a"
                        text: centerviewdatamodel.HVBatActlVoltage
                              === -65536 ? qsTr("--") : centerviewdatamodel.HVBatActlVoltage
                        font.pixelSize: 32
                        font.family: "Source Han Sans CN Normal"
                    }

                    Text {
                        id: unit13
                        color: "#2f3a4a"
                        text: qsTr("V")
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 24
                        font.family: "Source Han Sans CN Normal"
                    }
                    spacing: 8
                }
                anchors.bottomMargin: 0
                gradient: Gradient {
                    orientation: Gradient.Vertical
                    GradientStop {
                        position: 0
                        color: "#f1f9ff"
                    }

                    GradientStop {
                        position: 1
                        color: "#facee4f7"
                    }
                }
            }

            Rectangle {
                id: rectangle14
                x: 3
                y: 180
                width: 240
                height: 136
                radius: 8
                anchors.bottom: parent.bottom
                anchors.horizontalCenterOffset: 130
                anchors.horizontalCenter: parent.horizontalCenter
                Text {
                    id: text15
                    x: 20
                    y: 20
                    color: "#2f3a4a"
                    text: qsTr("动力电池电流")
                    font.pixelSize: 24
                    font.family: "Source Han Sans CN Normal"
                }

                Row {
                    id: row14
                    x: 20
                    y: 60
                    width: 200
                    height: 36
                    Text {
                        id: value14
                        color: "#2f3a4a"
                        text: centerviewdatamodel.ExchgCurnt
                        font.pixelSize: 32
                        font.family: "Source Han Sans CN Normal"
                    }

                    Text {
                        id: unit14
                        color: "#2f3a4a"
                        text: qsTr("A")
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 24
                        font.family: "Source Han Sans CN Normal"
                    }
                    spacing: 8
                }
                anchors.bottomMargin: 0
                gradient: Gradient {
                    orientation: Gradient.Vertical
                    GradientStop {
                        position: 0
                        color: "#f1f9ff"
                    }

                    GradientStop {
                        position: 1
                        color: "#facee4f7"
                    }
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;height:473;width:884}
}
##^##*/

