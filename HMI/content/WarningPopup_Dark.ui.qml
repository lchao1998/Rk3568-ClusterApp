

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
    width: 580
    height: 130

    Item {
        id: textAlarm_A
        visible: false
        anchors.fill: parent

        Image {
            id: door
            visible: warningpopupdatamodel.door_Pop === true
            source: "images/WarningPopup/DarkTheme/Red_Bg.png"
            fillMode: Image.PreserveAspectFit

            Text {
                id: text1
                y: 45
                color: "#ff0000"
                text: qsTr("请关闭车门")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
        }

        Image {
            id: seatBelt
            visible: warningpopupdatamodel.Seatbelt_Pop === true
            source: "images/WarningPopup/DarkTheme/Red_Bg.png"
            Text {
                id: text3
                y: 45
                color: "#ff0000"
                text: qsTr("安全带未系")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: tPMSPressureSta
            visible: warningpopupdatamodel.TPMSPressureStaFL_Pop
                     || warningpopupdatamodel.TPMSPressureStaFR_Pop
                     || warningpopupdatamodel.TPMSPressureStaRL_Pop
                     || warningpopupdatamodel.TPMSPressureStaRR_Pop
            source: "images/WarningPopup/DarkTheme/Yellow_Bg.png"
            Image {
                id: tpMSPressureSta
                y: 25
                width: 80
                height: 80
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/TirePressure.png"
                fillMode: Image.PreserveAspectFit
                anchors.leftMargin: 70
                anchors.verticalCenterOffset: 0
            }

            Text {
                id: low
                y: 45
                visible: warningpopupdatamodel.TPMSPressureStaFL_Pop === 2
                         || warningpopupdatamodel.TPMSPressureStaFR_Pop === 2
                         || warningpopupdatamodel.TPMSPressureStaRL_Pop === 2
                         || warningpopupdatamodel.TPMSPressureStaRR_Pop === 2
                color: "#ff9600"
                text: qsTr("轮胎气压低")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }

            Text {
                id: high
                y: 46
                visible: (warningpopupdatamodel.TPMSPressureStaFL_Pop === 1
                          || warningpopupdatamodel.TPMSPressureStaFR_Pop === 1
                          || warningpopupdatamodel.TPMSPressureStaRL_Pop === 1
                          || warningpopupdatamodel.TPMSPressureStaRR_Pop === 1)
                         && low.visible === false
                color: "#ff9600"
                text: qsTr("轮胎气压高")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }

            Text {
                id: hightemp
                y: 39
                visible: (warningpopupdatamodel.TPMSPressureStaFL_Pop === 3
                          || warningpopupdatamodel.TPMSPressureStaFR_Pop === 3
                          || warningpopupdatamodel.TPMSPressureStaRL_Pop === 3
                          || warningpopupdatamodel.TPMSPressureStaRR_Pop === 3)
                         && low.visible === false && high.visible === false
                color: "#ff9600"
                text: qsTr("轮胎温度高")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }

            Text {
                id: sensorFailure
                y: 37
                visible: (warningpopupdatamodel.TPMSPressureStaFL_Pop
                          === 4 || warningpopupdatamodel.TPMSPressureStaFR_Pop
                          === 4 || warningpopupdatamodel.TPMSPressureStaRL_Pop
                          === 4 || warningpopupdatamodel.TPMSPressureStaRR_Pop
                          === 4) && low.visible === false && high.visible
                         === false && hightemp.visible === false
                color: "#ff9600"
                text: qsTr("轮胎传感器故障")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: drivable
            visible: warningpopupdatamodel.Drivable_Pop === true
            source: "images/WarningPopup/DarkTheme/Green_Bg.png"
            Text {
                id: text4
                y: 45
                color: "#00d808"
                text: qsTr("车辆处于可行驶状态")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: overspeed
            visible: false
            source: "images/WarningPopup/DarkTheme/Red_Bg.png"
            Text {
                id: text11
                y: 45
                color: "#ff0000"
                text: qsTr("超速报警")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }
    }

    Item {
        id: textAlarm_B
        visible: false
        anchors.fill: parent

        Image {
            id: aBS
            visible: warningpopupdatamodel.ABSfailed_Pop === true
            source: "images/WarningPopup/DarkTheme/Yellow_Bg.png"
            fillMode: Image.PreserveAspectFit

            Image {
                id: abs
                y: 25
                width: 80
                height: 80
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/ABS.png"
                anchors.leftMargin: 70
                fillMode: Image.PreserveAspectFit
                anchors.verticalCenterOffset: 0
            }

            Text {
                id: text2
                y: 45
                color: "#ff9600"
                text: qsTr("ABS系统故障")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
        }

        Image {
            id: eSCFailed
            visible: warningpopupdatamodel.ESCFailed_Pop === true
            source: "images/WarningPopup/DarkTheme/Yellow_Bg.png"
            Image {
                id: escFailed
                y: 25
                width: 80
                height: 80
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/ESP.png"
                fillMode: Image.PreserveAspectFit
                anchors.leftMargin: 70
                anchors.verticalCenterOffset: 0
            }

            Text {
                id: text6
                y: 45
                color: "#ff9600"
                text: qsTr("ESC系统故障")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: hDCWorkSts
            visible: warningpopupdatamodel.HDCWorkSts_Pop === true
            source: "images/WarningPopup/DarkTheme/Red_Bg.png"
            Image {
                id: hdcWorkSts
                y: 25
                width: 80
                height: 80
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/SteepDescentFailure.png"
                fillMode: Image.PreserveAspectFit
                anchors.leftMargin: 70
                anchors.verticalCenterOffset: 0
            }

            Text {
                id: text7
                y: 45
                color: "#ff0000"
                text: qsTr("陡坡缓降系统故障")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: eBDFailed
            visible: warningpopupdatamodel.EBDFailed_Pop === true
            source: "images/WarningPopup/DarkTheme/Red_Bg.png"
            Image {
                id: ebdFailed
                y: 25
                width: 80
                height: 80
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/Parking.png"
                fillMode: Image.PreserveAspectFit
                anchors.leftMargin: 70
                anchors.verticalCenterOffset: 0
            }

            Text {
                id: text8
                y: 45
                color: "#ff0000"
                text: qsTr("制动系统故障")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: aVHSts
            visible: warningpopupdatamodel.AVHSts_Pop === true
            source: "images/WarningPopup/DarkTheme/Red_Bg.png"
            Image {
                id: avhSts
                y: 25
                width: 80
                height: 80
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/AutomaticParkingFailure.png"
                fillMode: Image.PreserveAspectFit
                anchors.leftMargin: 70
                anchors.verticalCenterOffset: 0
            }

            Text {
                id: text9
                y: 45
                color: "#ff0000"
                text: qsTr("自动驻车系统故障")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: basicElecSteerFailed
            visible: warningpopupdatamodel.BasicElecSteerFailed_Pop === true
            source: "images/WarningPopup/DarkTheme/Red_Bg.png"
            Image {
                id: basicelecSteerFailed
                y: 25
                width: 80
                height: 80
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/EPS.png"
                fillMode: Image.PreserveAspectFit
                anchors.leftMargin: 70
                anchors.verticalCenterOffset: 0
            }

            Text {
                id: text10
                y: 45
                color: "#ff0000"
                text: qsTr("电子转向系统故障")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: cruiseCtrlStaError
            visible: warningpopupdatamodel.CruiseCtrlStaError_Pop === true
            source: "images/WarningPopup/DarkTheme/Red_Bg.png"
            Image {
                id: cruisectrlStaError
                y: 25
                width: 80
                height: 80
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/ConstantCruisingFailure.png"
                fillMode: Image.PreserveAspectFit
                anchors.leftMargin: 70
                anchors.verticalCenterOffset: 0
            }

            Text {
                id: text12
                y: 45
                color: "#ff0000"
                text: qsTr("定速巡航系统故障")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: engineSta
            visible: warningpopupdatamodel.EngineSta_Pop === true
            source: "images/WarningPopup/DarkTheme/Red_Bg.png"
            Image {
                id: enginesta
                y: 25
                width: 80
                height: 80
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/EngineFailure.png"
                fillMode: Image.PreserveAspectFit
                anchors.leftMargin: 70
                anchors.verticalCenterOffset: 0
            }

            Text {
                id: text13
                y: 45
                color: "#ff0000"
                text: qsTr("发动机系统故障")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: transSta
            visible: warningpopupdatamodel.TransSta_Pop === true
            source: "images/WarningPopup/DarkTheme/Yellow_Bg.png"
            Image {
                id: transsta
                y: 25
                width: 80
                height: 80
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/TransSta.png"
                fillMode: Image.PreserveAspectFit
                anchors.leftMargin: 70
                anchors.verticalCenterOffset: 0
            }

            Text {
                id: text14
                y: 45
                color: "#ff9600"
                text: qsTr("变速箱故障")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: tPMSError
            visible: warningpopupdatamodel.TPMSError_Pop === true
            source: "images/WarningPopup/DarkTheme/Yellow_Bg.png"
            Image {
                id: tpMSError
                y: 25
                width: 80
                height: 80
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/TirePressure.png"
                fillMode: Image.PreserveAspectFit
                anchors.leftMargin: 70
                anchors.verticalCenterOffset: 0
            }

            Text {
                id: text15
                y: 45
                color: "#ff9600"
                text: qsTr("胎压系统故障")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: limpHomeSta
            visible: warningpopupdatamodel.LimpHomeSta_Pop === true
            source: "images/WarningPopup/DarkTheme/Yellow_Bg.png"
            Image {
                id: limphomeSta
                y: 25
                width: 80
                height: 80
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/Power_limitation.png"
                fillMode: Image.PreserveAspectFit
                anchors.leftMargin: 70
                anchors.verticalCenterOffset: 0
            }

            Text {
                id: text16
                y: 45
                color: "#ff9600"
                text: qsTr("驱动功率受限")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: pwrTrainHighTempWrning
            visible: warningpopupdatamodel.PwrTrainHighTempWrning_Pop === true
            source: "images/WarningPopup/DarkTheme/Red_Bg.png"
            Image {
                id: pwrtrainHighTempWrning
                y: 25
                width: 80
                height: 80
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/PowerBatteryOverHeated .png"
                fillMode: Image.PreserveAspectFit
                anchors.leftMargin: 70
                anchors.verticalCenterOffset: 0
            }

            Text {
                id: text17
                y: 45
                color: "#ff0000"
                text: qsTr("动力电池温度过高")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: pwrTrainConnectSta
            visible: warningpopupdatamodel.PwrTrainConnectSta_Pop === true
            source: "images/WarningPopup/DarkTheme/Yellow_Bg.png"
            Image {
                id: pwrtrainConnectSta
                y: 25
                width: 80
                height: 80
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/PowerBatteryDisconnection.png"
                fillMode: Image.PreserveAspectFit
                anchors.leftMargin: 70
                anchors.verticalCenterOffset: 0
            }

            Text {
                id: text18
                y: 45
                color: "#ff9600"
                text: qsTr("动力电池断开")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: motorHighTempWrning
            visible: warningpopupdatamodel.MotorHighTempWrning_Pop === true
            source: "images/WarningPopup/DarkTheme/Red_Bg.png"
            Image {
                id: motorhighTempWrning
                y: 25
                width: 80
                height: 80
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/Drive_motor.png"
                fillMode: Image.PreserveAspectFit
                anchors.leftMargin: 70
                anchors.verticalCenterOffset: 0
            }

            Text {
                id: text19
                y: 45
                color: "#ff0000"
                text: qsTr("电机及控制器过热")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: bMSSysFailSta
            visible: warningpopupdatamodel.BMSSysFailSta_Pop === true
            source: "images/WarningPopup/DarkTheme/Red_Bg.png"
            Image {
                id: bmSSysFailSta
                y: 25
                width: 80
                height: 80
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/Power_battery.png"
                fillMode: Image.PreserveAspectFit
                anchors.leftMargin: 70
                anchors.verticalCenterOffset: 0
            }

            Text {
                id: text20
                y: 45
                color: "#ff0000"
                text: qsTr("动力电池故障")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: drvMotorSta
            visible: warningpopupdatamodel.DrvMotorSta_Pop === true
            source: "images/WarningPopup/DarkTheme/Red_Bg.png"
            Image {
                id: drvmotorSta
                y: 25
                width: 80
                height: 80
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/Drive_motor.png"
                fillMode: Image.PreserveAspectFit
                anchors.leftMargin: 70
                anchors.verticalCenterOffset: 0
            }

            Text {
                id: text21
                y: 45
                color: "#ff0000"
                text: qsTr("电机故障")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: pCUFailSta
            visible: warningpopupdatamodel.PCUFailSta_Pop === true
            source: "images/WarningPopup/DarkTheme/Red_Bg.png"
            Image {
                id: pcUFailSta
                y: 25
                width: 80
                height: 80
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/dynamic_system.png"
                fillMode: Image.PreserveAspectFit
                anchors.leftMargin: 70
                anchors.verticalCenterOffset: 0
            }

            Text {
                id: text22
                y: 45
                color: "#ff0000"
                text: qsTr("动力系统故障")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: insulationWrning
            visible: warningpopupdatamodel.InsulationWrning_Pop === true
            source: "images/WarningPopup/DarkTheme/Red_Bg.png"
            Image {
                id: insulationwrning
                y: 25
                width: 80
                height: 80
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/InsulationFault.png"
                fillMode: Image.PreserveAspectFit
                anchors.leftMargin: 70
                anchors.verticalCenterOffset: 0
            }

            Text {
                id: text23
                y: 45
                color: "#ff0000"
                text: qsTr("绝缘故障")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: pASwarn
            visible: warningpopupdatamodel.PASwarn_Pop === true
            source: "images/WarningPopup/DarkTheme/Red_Bg.png"

            Text {
                id: text24
                y: 45
                color: "#ff0000"
                text: qsTr("雷达系统故障")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: pASSta
            visible: warningpopupdatamodel.PASSta_Pop === true
            source: "images/WarningPopup/DarkTheme/Red_Bg.png"
            Text {
                id: text25
                y: 45
                color: "#ff0000"
                text: qsTr("雷达传感器故障")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: sRSError
            visible: warningpopupdatamodel.SRSError_Pop === true
            source: "images/WarningPopup/DarkTheme/Red_Bg.png"
            Image {
                id: srSError
                y: 25
                width: 80
                height: 80
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/SRSError.png"
                fillMode: Image.PreserveAspectFit
                anchors.leftMargin: 70
                anchors.verticalCenterOffset: 0
            }

            Text {
                id: text26
                y: 45
                color: "#ff0000"
                text: qsTr("安全气囊系统故障")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: batSOCRptWarning
            visible: warningpopupdatamodel.BatSOCRptWarning_Pop === true
            source: "images/WarningPopup/DarkTheme/Yellow_Bg.png"
            Image {
                id: batsOCRptWarning
                y: 25
                width: 80
                height: 80
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/ElectricQuantityAlarm.png"
                fillMode: Image.PreserveAspectFit
                anchors.leftMargin: 70
                anchors.verticalCenterOffset: 0
            }

            Text {
                id: text27
                y: 45
                color: "#ff9600"
                text: qsTr("动力电池电量低")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }
    }

    Item {
        id: textAlarm_C
        visible: false
        anchors.fill: parent
        Image {
            id: lowBrake
            x: 0
            y: 0
            visible: warningpopupdatamodel.HU_brakeliquidlevel_Pop === true
            source: "images/WarningPopup/DarkTheme/Red_Bg.png"
            fillMode: Image.PreserveAspectFit

            Image {
                id: lowBrakeLevel
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/LowBrakeLevel.png"
                anchors.leftMargin: 70
                fillMode: Image.PreserveAspectFit
            }
            Text {
                id: text5
                y: 45
                color: "#ff0000"
                text: qsTr("制动液位低")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
        }

        Image {
            id: highCoolantTemperature
            visible: warningpopupdatamodel.highCoolantTemperature_Pop === true
            source: "images/WarningPopup/DarkTheme/Red_Bg.png"
            Image {
                id: highcoolantTemperature
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/WaterTemperature_High.png"
                anchors.leftMargin: 70
                fillMode: Image.PreserveAspectFit
            }

            Text {
                id: text28
                y: 45
                color: "#ff0000"
                text: qsTr("冷却液温度高")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: hU_MachineOilPre
            visible: warningpopupdatamodel.HU_MachineOilPre_Pop === true
            source: "images/WarningPopup/DarkTheme/Red_Bg.png"
            Image {
                id: hu_MachineOilPre
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/MachineOilPress.png"
                anchors.leftMargin: 70
                fillMode: Image.PreserveAspectFit
            }

            Text {
                id: text29
                y: 45
                color: "#ff0000"
                text: qsTr("机油压力低")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: lowFuel
            visible: warningpopupdatamodel.lowFuel_Pop === true
            source: "images/WarningPopup/DarkTheme/Yellow_Bg.png"
            Image {
                id: lowfuel
                y: 25
                width: 80
                height: 80
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/oil_low.png"
                fillMode: Image.PreserveAspectFit
                anchors.leftMargin: 70
                anchors.verticalCenterOffset: 0
            }

            Text {
                id: text30
                y: 45
                color: "#ff9600"
                text: qsTr("燃油液位低")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: pALAresponse
            visible: false //warningpopupdatamodel.PALAresponse_Pop === true
            source: "images/WarningPopup/DarkTheme/Yellow_Bg.png"
            Image {
                id: paLAresponse
                y: 25
                width: 80
                height: 80
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/ESP_Off.png"
                fillMode: Image.PreserveAspectFit
                anchors.leftMargin: 70
                anchors.verticalCenterOffset: 0
            }

            Text {
                id: text31
                y: 45
                color: "#ff9600"
                text: qsTr("ESC系统已关闭")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: tPMSUnLearned
            visible: warningpopupdatamodel.TPMSUnLearned_Pop === true
            source: "images/WarningPopup/DarkTheme/Yellow_Bg.png"
            Image {
                id: tpMSUnLearned
                y: 25
                width: 80
                height: 80
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/TirePressure.png"
                fillMode: Image.PreserveAspectFit
                anchors.leftMargin: 70
                anchors.verticalCenterOffset: 0
            }

            Text {
                id: text32
                y: 45
                color: "#ff9600"
                text: qsTr("胎压系统未学习")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: cruiseCtrlStaActive
            visible: warningpopupdatamodel.CruiseCtrlStaActive_Pop === true
            source: "images/WarningPopup/DarkTheme/Green_Bg.png"

            Image {
                id: constantCruising
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/ConstantCruising.png"
                anchors.leftMargin: 70
                fillMode: Image.PreserveAspectFit
            }
            fillMode: Image.PreserveAspectFit
            Text {
                id: text33
                y: 45
                color: "#00d808"
                text: qsTr("定速巡航已激活")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
        }

        Image {
            id: vSPsta
            visible: warningpopupdatamodel.VSPsta_Pop === true
            source: "images/WarningPopup/DarkTheme/Yellow_Bg.png"
            Image {
                id: vsPsta
                y: 25
                width: 80
                height: 80
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                source: "images/WarningPopup/icon/PedestrianPromptClosure.png"
                fillMode: Image.PreserveAspectFit
                anchors.leftMargin: 70
                anchors.verticalCenterOffset: 0
            }

            Text {
                id: text34
                y: 45
                color: "#ff9600"
                text: qsTr("行人提醒装置已关闭")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 28
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Source Han Sans CN Normal"
            }
            fillMode: Image.PreserveAspectFit
        }
    }

    Image {
        id: bMSFailure
        x: 0
        y: 0
        visible: centerviewdatamodel.BMSErrorCodes
        source: "images/WarningPopup/DarkTheme/Red_Bg.png"
        fillMode: Image.PreserveAspectFit

        Text {
            id: text35
            y: 45
            visible: centerviewdatamodel.BMSErrorCodes === 1
            color: "#ff0000"
            text: qsTr("动力系统三级故障")
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 28
            font.family: "Source Han Sans CN Normal"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            id: text36
            y: 45
            visible: centerviewdatamodel.BMSErrorCodes === 2
            color: "#ff0000"
            text: qsTr("动力系统二级故障")
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 28
            font.family: "Source Han Sans CN Normal"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            id: text37
            y: 45
            visible: centerviewdatamodel.BMSErrorCodes === 3
            color: "#ff0000"
            text: qsTr("动力系统一级故障")
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 28
            font.family: "Source Han Sans CN Normal"
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    PropertyAnimation {
        id: propertyAnimation
        target: bMSFailure
        property: "visible"
        running: centerviewdatamodel.BMSErrorCodes
        duration: 5000
        from: true
        to: false
    }
}

/*##^##
Designer {
    D{i:0;height:130;width:580}D{i:108}D{i:109}D{i:106}
}
##^##*/

