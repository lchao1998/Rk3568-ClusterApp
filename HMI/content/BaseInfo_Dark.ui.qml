

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

    Item {
        id: time_Gear_Temperature
        width: 370
        height: 84
        anchors.top: parent.top
        anchors.topMargin: 24
        anchors.horizontalCenter: parent.horizontalCenter

        Text {
            id: time
            color: "#ffffff"
            text: baseinfodatamodel.BJS_Time
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 40
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.horizontalCenterOffset: -150
            anchors.horizontalCenter: gear_Bg.horizontalCenter
            font.family: "Source Han Sans CN Normal"
        }

        Image {
            id: gear_Bg
            anchors.verticalCenter: parent.verticalCenter
            source: "images/BaseInfo/DarkTheme/Gear_Bg.png"
            anchors.horizontalCenter: parent.horizontalCenter
            fillMode: Image.PreserveAspectFit

            Text {
                id: gear_Text
                color: "#ffffff"
                text: baseinfodatamodel.TranGearPos
                anchors.fill: parent
                font.pixelSize: 55
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: "Source Han Sans CN Normal"
            }
        }

        Text {
            id: temperature
            color: "#ffffff"
            text: (baseinfodatamodel.EnvirTemp
                   === 255 ? qsTr("--") : baseinfodatamodel.EnvirTemp) + qsTr(
                      "℃")
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 40
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.horizontalCenterOffset: 150
            anchors.horizontalCenter: gear_Bg.horizontalCenter
            font.family: "Source Han Sans CN Normal"
        }
    }

    Row {
        id: odo
        x: 476
        y: 668
        width: 253
        height: 24
        anchors.bottom: parent.bottom
        spacing: 20
        anchors.bottomMargin: 28

        Text {
            id: odo_Lab
            height: 24
            color: "#6080ad"
            text: qsTr("ODO")
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 28
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN Normal"
        }

        Text {
            id: odo_Value
            height: 24
            color: "#ffffff"
            text: baseinfodatamodel.HU_Totalodometer
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 32
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN Normal"
        }

        Text {
            id: odo_Unit
            color: "#6080ad"
            text: qsTr("km")
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 24
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN Normal"
        }
    }

    Row {
        id: tripA
        x: 1218
        y: 668
        width: 253
        height: 24
        visible: true
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 28
        spacing: 20
        Text {
            id: tripA_Lab
            height: 24
            color: "#6080ad"
            text: qsTr("TRIP A")
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 28
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN Normal"
        }

        Text {
            id: tripA_Value
            height: 24
            color: "#ffffff"
            text: (baseinfodatamodel.HU_TripAOdometer).toFixed(2)
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 32
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN Normal"
        }

        Text {
            id: tripA_Unit
            color: "#6080ad"
            text: qsTr("km")
            font.pixelSize: 24
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN Normal"
        }
    }

    Row {
        id: tripB
        x: 1218
        y: 661
        width: 253
        height: 24
        visible: false
        anchors.bottom: parent.bottom
        Text {
            id: tripB_Lab
            height: 24
            color: "#6080ad"
            text: qsTr("TRIP B")
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 28
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN Normal"
        }

        Text {
            id: tripB_Value
            height: 24
            color: "#ffffff"
            text: baseinfodatamodel.HU_TripBOdometer
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 32
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN Normal"
        }

        Text {
            id: tripB_Unit
            color: "#6080ad"
            text: qsTr("km")
            font.pixelSize: 24
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.family: "Source Han Sans CN Normal"
        }
        anchors.bottomMargin: 28
        spacing: 20
    }

    Item {
        id: item_Oil
        visible: false
        anchors.fill: parent

        Row {
            id: oil
            x: 50
            y: 660
            width: 350
            height: 60
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            spacing: 15
            anchors.leftMargin: 50
            anchors.bottomMargin: 10

            Item {
                id: oil_icon
                width: 60
                height: 60

                Image {
                    id: oil_nor
                    visible: !telltaledatamodel.lowFuel
                    source: "images/BaseInfo/DarkTheme/oil_nor.png"
                    fillMode: Image.PreserveAspectFit
                }
                Image {
                    id: oil_low
                    visible: telltaledatamodel.lowFuel
                    source: "images/BaseInfo/DarkTheme/oil_low.png"
                    fillMode: Image.PreserveAspectFit
                }
            }

            Text {
                id: oil_E
                color: "#ffffff"
                text: qsTr("E")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 32
                font.family: "Source Han Sans CN Normal"
            }

            WaterAndOilProgress_Dark {
                id: oilProgress
                anchors.verticalCenter: parent.verticalCenter
                value: (baseinfodatamodel.HU_engineoil / 100) * 200 - 200
            }

            Text {
                id: oil_F
                color: "#ffffff"
                text: qsTr("F")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 32
                font.family: "Source Han Sans CN Normal"
            }
        }

        Row {
            id: water
            x: 44
            y: 659
            width: 350
            height: 60
            anchors.left: parent.left
            anchors.bottom: parent.bottom

            Text {
                id: water_C
                color: "#ffffff"
                text: qsTr("C")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 32
                font.family: "Source Han Sans CN Normal"
            }

            WaterAndOilProgress_Dark {
                id: waterProgress
                anchors.verticalCenter: parent.verticalCenter
                value: (baseinfodatamodel.HU_EngCoolantTemp / 150) * 200 - 200
            }

            Text {
                id: water_H
                color: "#ffffff"
                text: qsTr("H")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 32
                font.family: "Source Han Sans CN Normal"
            }

            anchors.leftMargin: 1546
            anchors.bottomMargin: 10
            spacing: 15

            Item {
                id: waterTemperature_icon
                width: 60
                height: 60

                Image {
                    id: waterTemperature_Normal
                    visible: !telltaledatamodel.highCoolantTemperature
                    source: "images/BaseInfo/DarkTheme/WaterTemperature_Normal.png"
                    fillMode: Image.PreserveAspectFit
                }
                Image {
                    id: waterTemperature_High
                    y: 0
                    visible: telltaledatamodel.highCoolantTemperature
                    source: "images/BaseInfo/DarkTheme/WaterTemperature_High.png"
                    fillMode: Image.PreserveAspectFit
                }
            }
        }
    }

    Item {
        id: item_Electric
        width: 1920
        height: 720
        visible: true

        Row {
            id: energy_Recovery
            x: 50
            y: 660
            width: 350
            height: 60
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            spacing: 15
            anchors.leftMargin: 50
            anchors.bottomMargin: 10

            Image {
                id: energy_Recovery_Icon
                source: "images/BaseInfo/DarkTheme/Energy_Recovery_Icon.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: energy_Recovery_Bg
                anchors.verticalCenter: parent.verticalCenter
                source: "images/BaseInfo/Energy_Recovery_Bg.png"
                clip: true
                fillMode: Image.PreserveAspectFit

                Image {
                    id: energy_Recovery_Fg_1
                    x: -102
                    visible: baseinfodatamodel.recupLevelSta === 1
                    source: "images/BaseInfo/Energy_Recovery_Fg.png"
                    fillMode: Image.PreserveAspectFit
                }

                Image {
                    id: energy_Recovery_Fg_2
                    visible: baseinfodatamodel.recupLevelSta === 2
                    source: "images/BaseInfo/Energy_Recovery_Fg.png"
                    fillMode: Image.PreserveAspectFit
                }
            }
        }

        Row {
            id: endurance_Power
            x: 44
            y: 650
            width: 222
            height: 60
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            spacing: 20
            anchors.leftMargin: 1670
            anchors.bottomMargin: 10

            Image {
                id: endurance_Power_Icon
                x: 0
                anchors.verticalCenter: parent.verticalCenter
                source: "images/BaseInfo/Endurance_Power.png"
                clip: true
                fillMode: Image.PreserveAspectFit

                Image {
                    id: endurance_Power_Fg
                    x: 2
                    y: 2
                    width: (centerviewdatamodel.BatSOCRpt / 100) * 52
                    height: 24
                    source: centerviewdatamodel.BatSOCRpt >= 10 ? "images/BaseInfo/Endurance_Power_Fg.png" : "images/BaseInfo/Endurance_Power_YellowFg.png"
                    fillMode: Image.Stretch
                }
            }

            Text {
                id: endurance_Power_Value
                height: 24
                color: "#ffffff"
                text: centerviewdatamodel.HU_RemainRange
                      === -65536 ? qsTr("----") : centerviewdatamodel.HU_RemainRange
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 32
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: "Source Han Sans CN Normal"
            }

            Text {
                id: endurance_Power_Unit
                color: "#6080ad"
                text: qsTr("km")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 24
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.family: "Source Han Sans CN Normal"
            }
        }

        Image {
            id: rEADY
            y: 135
            visible: baseinfodatamodel.PTActlOprtMode === 2
            source: "images/BaseInfo/READY.png"
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: wait
            y: 135
            visible: baseinfodatamodel.PTActlOprtMode === 1
            source: "images/BaseInfo/Wait.png"
            anchors.horizontalCenter: parent.horizontalCenter
            fillMode: Image.PreserveAspectFit
        }

        Item {
            id: driveMode
            width: 138
            height: 25
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 28
            anchors.horizontalCenter: parent.horizontalCenter

            Image {
                id: eCO
                y: 0
                visible: baseinfodatamodel.drivemode === 0
                source: "images/BaseInfo/ECO.png"
                anchors.horizontalCenter: parent.horizontalCenter
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: nORMAL
                y: 0
                visible: baseinfodatamodel.drivemode === 1
                source: "images/BaseInfo/NORMAL.png"
                anchors.horizontalCenter: parent.horizontalCenter
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: sPORT
                y: 0
                visible: baseinfodatamodel.drivemode === 2
                source: "images/BaseInfo/SPORT.png"
                anchors.horizontalCenter: parent.horizontalCenter
                fillMode: Image.PreserveAspectFit
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5;height:720;width:1920}
}
##^##*/

