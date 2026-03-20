

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

    Row {
        id: leftLamp_First
        x: 43
        y: 34
        width: 60
        height: 60
        spacing: 14

        Item {
            id: mainSeatBeltItem
            width: 60
            height: 60

            Image {
                id: mainSeatBelt
                visible: telltaledatamodel.DrvSeatbeltBucklestatus === 0
                anchors.fill: parent
                source: "images/TT/MainSeatBelt.png"
                fillMode: Image.PreserveAspectFit

                SequentialAnimation {
                    id: sequentialAnimation6
                    loops: 60
                    running: telltaledatamodel.DrvSeatbeltBucklestatus === 2
                    PropertyAnimation {
                        id: propertyAnimation12
                        target: mainSeatBelt
                        property: "visible"
                        duration: 1000
                        to: false
                    }

                    PropertyAnimation {
                        id: propertyAnimation13
                        target: mainSeatBelt
                        property: "visible"
                        duration: 1000
                        to: true
                    }
                }
            }
        }

        Image {
            id: pAssSeatbeltBucklestatus
            x: 0
            y: 0
            width: 60
            height: 60
            source: telltaledatamodel.PAssSeatbeltBucklestatus
                    && telltaledatamodel.PassSeatOccSta ? "images/TT/PAssSeatbeltBucklestatus.png" : ""
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: frontFogLamp
            x: 0
            y: 0
            width: 60
            height: 60
            source: telltaledatamodel.FrontFogLampSta ? "images/TT/FrontFogLamp.png" : ""
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: rearFogLamp
            x: 0
            y: 0
            width: 60
            height: 60
            source: telltaledatamodel.rearFogLampSta ? "images/TT/RearFogLamp.png" : ""
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: automaticHyperBeam
            x: 0
            y: 0
            width: 60
            height: 60
            source: telltaledatamodel.autohighbeam ? "images/TT/AutomaticHyperBeam.png" : ""
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: highBeamLamp
            x: 0
            y: 0
            width: 60
            height: 60
            source: telltaledatamodel.highbeam
                    || telltaledatamodel.Flashbeam ? "images/TT/HighBeamLamp.png" : ""
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: nearlightLamp
            x: 0
            y: 0
            width: 60
            height: 60
            source: telltaledatamodel.lowbeam ? "images/TT/Near-lightLamp.png" : ""
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: positionLight
            x: 0
            y: 0
            width: 60
            height: 60
            source: telltaledatamodel.positionlamp ? "images/TT/PositionLight.png" : ""
            fillMode: Image.PreserveAspectFit
        }
    }

    Image {
        id: leftTurnLight
        x: 635
        y: 24
        width: 80
        height: 80
        source: telltaledatamodel.leftTurnlamp === true
                || telltaledatamodel.hazardIsSignaling === true ? "images/TT/LeftTurnLight.png" : ""
        fillMode: Image.PreserveAspectFit
    }

    Image {
        id: rightTurnLight
        x: 1205
        y: 25
        width: 80
        height: 80
        source: telltaledatamodel.rightTurnlamp === true
                || telltaledatamodel.hazardIsSignaling
                === true ? "images/TT/RightTurnLight.png" : ""
        fillMode: Image.PreserveAspectFit
    }

    Row {
        id: rightLamp_First
        x: 1299
        y: 34
        width: 60
        height: 60
        spacing: 14

        Image {
            id: engineFailure
            x: 0
            y: 0
            width: 60
            height: 60
            source: telltaledatamodel.EngineSta ? "images/TT/EngineFailure.png" : ""
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: machineOilPress
            x: 0
            y: 0
            width: 60
            height: 60
            source: telltaledatamodel.HU_MachineOilPre ? "images/TT/MachineOilPress.png" : ""
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: aBS
            x: 0
            y: 0
            width: 60
            height: 60
            source: telltaledatamodel.ABSfailed ? "images/TT/ABS.png" : ""
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: sRSError
            x: 0
            y: 0
            width: 60
            height: 60
            source: telltaledatamodel.SRSError ? "images/TT/SRSError.png" : ""
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: transSta
            x: 0
            y: 0
            width: 60
            height: 60
            source: telltaledatamodel.TransSta ? "images/TT/TransSta.png" : ""
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: eDBFailed
            x: 0
            y: 0
            width: 60
            height: 60
            source: telltaledatamodel.EBDFailed ? "images/TT/EBDFailed.png" : ""
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: parking
            x: 0
            y: 0
            width: 60
            height: 60
            source: telltaledatamodel.ParkLampSta ? "images/TT/Parking.png" : ""
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: lowBrakeLevel
            x: 0
            y: 0
            width: 60
            height: 60
            source: telltaledatamodel.HU_brakeliquidlevel ? "images/TT/LowBrakeLevel.png" : ""
            fillMode: Image.PreserveAspectFit
        }
    }

    Item {
        id: item_Oil
        width: 1920
        height: 720
        visible: false

        Row {
            id: leftLamp_Second_Oil
            x: 43
            y: 114
            width: 60
            height: 60
            spacing: 14

            Image {
                id: ePS
                x: 0
                y: 0
                width: 60
                height: 60
                source: telltaledatamodel.BasicElecSteerFailed ? "images/TT/EPS.png" : ""
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: maintenance_light
                x: 0
                y: 0
                width: 60
                height: 60
                source: "images/TT/Maintenance _light.png"
                fillMode: Image.PreserveAspectFit
            }

            Item {
                id: steepDescentItem
                x: 0
                y: 0
                width: 60
                height: 60

                Image {
                    id: steepDescent
                    x: -74
                    y: 0
                    visible: telltaledatamodel.HDCWorkSts === 1
                    anchors.fill: parent
                    source: "images/TT/SteepDescent.png"
                    fillMode: Image.PreserveAspectFit

                    SequentialAnimation {
                        id: sequentialAnimation
                        alwaysRunToEnd: true
                        loops: -1
                        running: telltaledatamodel.HDCWorkSts === 1

                        PropertyAnimation {
                            id: propertyAnimation
                            target: steepDescent
                            property: "visible"
                            duration: 500
                            to: true
                        }

                        PropertyAnimation {
                            id: propertyAnimation1
                            target: steepDescent
                            property: "visible"
                            duration: 500
                            to: false
                        }
                    }
                }
                Image {
                    id: steepDescentFailure
                    x: -74
                    y: 0
                    visible: telltaledatamodel.HDCWorkSts === 2
                    anchors.fill: parent
                    source: "images/TT/SteepDescentFailure.png"
                    fillMode: Image.PreserveAspectFit
                }
            }

            Item {
                id: automaticParkingItem
                x: 0
                y: 0
                width: 60
                height: 60

                Image {
                    id: automaticParking
                    x: 0
                    y: 0
                    visible: telltaledatamodel.AVHSts === 2
                    source: "images/TT/AutomaticParking.png"
                    fillMode: Image.PreserveAspectFit
                }

                Image {
                    id: automaticParkingFailure
                    x: 0
                    y: 0
                    visible: telltaledatamodel.AVHSts === 3
                    source: "images/TT/AutomaticParkingFailure.png"
                    fillMode: Image.PreserveAspectFit
                }
            }

            Item {
                id: constantCruisingItem
                x: 0
                y: 0
                width: 60
                height: 60

                Image {
                    id: constantCruising
                    x: 0
                    y: 0
                    visible: telltaledatamodel.CruiseCtrlSta === 2
                    source: "images/TT/ConstantCruising.png"
                    fillMode: Image.PreserveAspectFit
                }

                Image {
                    id: constantCruisingFailure
                    x: 0
                    y: 0
                    visible: telltaledatamodel.CruiseCtrlSta === 3
                    source: "images/TT/ConstantCruisingFailure.png"
                    fillMode: Image.PreserveAspectFit
                }
            }

            Image {
                id: pEPS
                x: 0
                y: 0
                width: 60
                height: 60
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: batteryFailure
                x: 0
                y: 0
                width: 60
                height: 60
                source: telltaledatamodel.lowbatterycharge ? "images/TT/BatteryFailure.png" : ""
                fillMode: Image.PreserveAspectFit
            }
        }

        Row {
            id: rightLamp_Second_Oil
            x: 1521
            y: 114
            width: 60
            height: 60
            spacing: 14

            Item {
                id: tirePressureItem
                x: 0
                y: 0
                width: 60
                height: 60

                Image {
                    id: tirePressure
                    x: 0
                    y: 0
                    width: 60
                    height: 60
                    visible: telltaledatamodel.TPMSSta
                             || telltaledatamodel.TPMSPressureStaFL
                             || telltaledatamodel.TPMSPressureStaFR
                             || telltaledatamodel.TPMSPressureStaRL
                             || telltaledatamodel.TPMSPressureStaRR
                    source: "images/TT/TirePressure.png"
                    fillMode: Image.PreserveAspectFit

                    SequentialAnimation {
                        id: sequentialAnimation1
                        running: telltaledatamodel.TPMSSta === 2
                        loops: -1

                        PropertyAnimation {
                            id: propertyAnimation2
                            target: tirePressure
                            property: "visible"
                            duration: 500
                            to: true
                        }

                        PropertyAnimation {
                            id: propertyAnimation3
                            target: tirePressure
                            property: "visible"
                            duration: 500
                            to: false
                        }
                    }
                }
            }

            Image {
                id: engineAntitheft
                x: 0
                y: 0
                width: 60
                height: 60
                source: telltaledatamodel.IMMOPCUauthen ? "images/TT/EngineAnti-theft.png" : ""
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: ePC
                x: 0
                y: 0
                width: 60
                height: 60
                source: telltaledatamodel.EPCwarn ? "images/TT/EPC.png" : ""
                fillMode: Image.PreserveAspectFit
            }

            Item {
                id: escItem
                x: 0
                y: 0
                width: 60
                height: 60

                Image {
                    id: eSC
                    x: 0
                    y: 0
                    visible: telltaledatamodel.ESPActiveSta
                             || telltaledatamodel.ESCFailed
                    source: "images/TT/ESP.png"
                    fillMode: Image.PreserveAspectFit

                    SequentialAnimation {
                        id: sequentialAnimation2
                        running: telltaledatamodel.ESPActiveSta
                                 && telltaledatamodel.ESCFailed === false
                        loops: -1

                        PropertyAnimation {
                            id: propertyAnimation4
                            target: eSC
                            property: "visible"
                            duration: 500
                            to: true
                        }

                        PropertyAnimation {
                            id: propertyAnimation5
                            target: eSC
                            property: "visible"
                            duration: 500
                            to: false
                        }
                    }
                }

                Image {
                    id: eSC_Off
                    x: 0
                    y: 0
                    visible: telltaledatamodel.PALAresponse
                    source: "images/TT/ESP_Off.png"
                    fillMode: Image.PreserveAspectFit
                }
            }

            Image {
                id: open_door
                x: 0
                y: 0
                width: 60
                height: 60
                source: telltaledatamodel.doorajarFL
                        || telltaledatamodel.doorajarFR
                        || telltaledatamodel.doorajarRL
                        || telltaledatamodel.doorajarRR
                        || telltaledatamodel.HoodSta
                        || telltaledatamodel.TrunkSta ? "images/TT/Open_door.png" : ""
                fillMode: Image.PreserveAspectFit
            }
        }
    }

    Item {
        id: item_Electric
        width: 1920
        height: 720
        visible: true

        Row {
            id: leftLamp_Second_Electric
            x: 43
            y: 114
            width: 60
            height: 60
            Image {
                id: ePS1
                x: 0
                y: 0
                width: 60
                height: 60
                source: telltaledatamodel.BasicElecSteerFailed ? "images/TT/EPS.png" : ""
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: maintenance_light1
                x: 0
                y: 0
                width: 60
                height: 60
                source: telltaledatamodel.HU_VehicleMainLamp ? "images/TT/Maintenance _light.png" : ""
                fillMode: Image.PreserveAspectFit
            }

            Item {
                id: steepDescentItem1
                x: 0
                y: 0
                width: 60
                height: 60
                Image {
                    id: steepDescent1
                    x: -74
                    y: 0
                    visible: telltaledatamodel.HDCWorkSts === 1
                    anchors.fill: parent
                    source: "images/TT/SteepDescent.png"
                    fillMode: Image.PreserveAspectFit
                    SequentialAnimation {
                        id: sequentialAnimation3
                        alwaysRunToEnd: true
                        loops: -1
                        running: telltaledatamodel.HDCWorkSts === 1

                        PropertyAnimation {
                            id: propertyAnimation6
                            target: steepDescent1
                            property: "visible"
                            duration: 500
                            to: true
                        }

                        PropertyAnimation {
                            id: propertyAnimation7
                            target: steepDescent1
                            property: "visible"
                            duration: 500
                            to: false
                        }
                    }
                }

                Image {
                    id: steepDescentFailure1
                    x: -74
                    y: 0
                    anchors.fill: parent
                    visible: telltaledatamodel.HDCWorkSts === 2
                    source: "images/TT/SteepDescentFailure.png"
                    fillMode: Image.PreserveAspectFit
                }
            }

            Item {
                id: automaticParkingItem1
                x: 0
                y: 0
                width: 60
                height: 60
                Image {
                    id: automaticParking1
                    x: 0
                    y: 0
                    visible: telltaledatamodel.AVHSts === 2
                    source: "images/TT/AutomaticParking.png"
                    fillMode: Image.PreserveAspectFit
                }

                Image {
                    id: automaticParkingFailure1
                    x: 0
                    y: 0
                    visible: telltaledatamodel.AVHSts === 3
                    source: "images/TT/AutomaticParkingFailure.png"
                    fillMode: Image.PreserveAspectFit
                }
            }

            Item {
                id: constantCruisingItem1
                x: 0
                y: 0
                width: 60
                height: 60
                Image {
                    id: constantCruising1
                    x: 0
                    y: 0
                    visible: telltaledatamodel.CruiseCtrlSta === 2
                    source: "images/TT/ConstantCruising.png"
                    fillMode: Image.PreserveAspectFit
                }

                Image {
                    id: constantCruisingFailure1
                    x: 0
                    y: 0
                    visible: telltaledatamodel.CruiseCtrlSta === 3
                    source: "images/TT/ConstantCruisingFailure.png"
                    fillMode: Image.PreserveAspectFit
                }
            }

            Image {
                id: pEPS1
                x: 0
                y: 0
                width: 60
                height: 60
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: power_battery
                x: 0
                y: 0
                width: 60
                height: 60
                source: centerviewdatamodel.BMSErrorCodes ? "images/TT/Power_battery.png" : ""
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: drive_motor
                x: 0
                y: 0
                width: 60
                height: 60
                source: telltaledatamodel.MotorHighTempWrning
                        || telltaledatamodel.DrvMotorSta ? "images/TT/Drive_motor.png" : ""
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: batteryFailure1
                x: 0
                y: 0
                width: 60
                height: 60
                source: telltaledatamodel.lowbatterycharge ? "images/TT/BatteryFailure.png" : ""
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: powerBatteryDisconnection
                x: 0
                y: 0
                width: 60
                height: 60
                source: "" //!telltaledatamodel.PwrTrainConnectSta ? "images/TT/PowerBatteryDisconnection.png" : ""
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: powerBatteryOverHeated
                x: 0
                y: 0
                width: 60
                height: 60
                source: telltaledatamodel.PwrTrainHighTempWrning ? "images/TT/PowerBatteryOverHeated .png" : ""
                fillMode: Image.PreserveAspectFit
            }
            spacing: 14
        }

        Row {
            id: rightLamp_Second_Electric
            x: 1151
            y: 114
            width: 60
            height: 60
            Item {
                id: tirePressureItem1
                x: 0
                y: 0
                width: 60
                height: 60
                Image {
                    id: tirePressure1
                    x: 0
                    y: 0
                    width: 60
                    height: 60
                    visible: telltaledatamodel.TPMSSta
                             || telltaledatamodel.TPMSPressureStaFL > 1
                             || telltaledatamodel.TPMSPressureStaFR > 1
                             || telltaledatamodel.TPMSPressureStaRL > 1
                             || telltaledatamodel.TPMSPressureStaRR > 1
                    source: "images/TT/TirePressure.png"
                    fillMode: Image.PreserveAspectFit
                    SequentialAnimation {
                        id: sequentialAnimation4
                        loops: -1
                        running: telltaledatamodel.TPMSSta === 2

                        PropertyAnimation {
                            id: propertyAnimation8
                            target: tirePressure1
                            property: "visible"
                            duration: 500
                            to: true
                        }

                        PropertyAnimation {
                            id: propertyAnimation9
                            target: tirePressure1
                            property: "visible"
                            duration: 500
                            to: false
                        }
                    }
                }
            }

            Image {
                id: charging_connection
                x: 0
                y: 0
                width: 60
                height: 60
                source: telltaledatamodel.InletConnctSta ? "images/TT/Charging_connection.png" : ""
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: pedestrianPromptClosure
                x: 0
                y: 0
                width: 60
                height: 60
                source: telltaledatamodel.VSPsta ? "images/TT/PedestrianPromptClosure.png" : ""
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: power_limitation
                x: 0
                y: 0
                width: 60
                height: 60
                source: telltaledatamodel.LimpHomeSta ? "images/TT/Power_limitation.png" : ""
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: insulationFault
                x: 0
                y: 0
                width: 60
                height: 60
                source: telltaledatamodel.InsulationWrning ? "images/TT/InsulationFault.png" : ""
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: dynamic_system
                x: 0
                y: 0
                width: 60
                height: 60
                source: telltaledatamodel.PCUFailSta ? "images/TT/dynamic_system.png" : ""
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: engineAntitheft1
                x: 0
                y: 0
                width: 60
                height: 60
                source: telltaledatamodel.IMMOPCUauthen ? "images/TT/EngineAnti-theft.png" : ""
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: ePC1
                x: 0
                y: 0
                width: 60
                height: 60
                source: telltaledatamodel.EPCwarn ? "images/TT/EPC.png" : ""
                fillMode: Image.PreserveAspectFit
            }

            Item {
                id: escItem1
                x: 0
                y: 0
                width: 60
                height: 60
                Image {
                    id: eSC1
                    x: 0
                    y: 0
                    visible: telltaledatamodel.ESPActiveSta
                             || telltaledatamodel.ESCFailed
                    source: "images/TT/ESP.png"
                    fillMode: Image.PreserveAspectFit
                    SequentialAnimation {
                        id: sequentialAnimation5
                        loops: -1
                        running: telltaledatamodel.ESPActiveSta
                                 && telltaledatamodel.ESCFailed === false

                        PropertyAnimation {
                            id: propertyAnimation10
                            target: eSC1
                            property: "visible"
                            duration: 500
                            to: true
                        }

                        PropertyAnimation {
                            id: propertyAnimation11
                            target: eSC1
                            property: "visible"
                            duration: 500
                            to: false
                        }
                    }
                }

                Image {
                    id: eSC_Off1
                    x: 0
                    y: 0
                    visible: telltaledatamodel.PALAresponse
                    source: "images/TT/ESP_Off.png"
                    fillMode: Image.PreserveAspectFit
                }
            }

            Image {
                id: open_door1
                x: 0
                y: 0
                width: 60
                height: 60
                source: telltaledatamodel.doorajarFL
                        || telltaledatamodel.doorajarFR
                        || telltaledatamodel.doorajarRL
                        || telltaledatamodel.doorajarRR
                        || telltaledatamodel.HoodSta
                        || telltaledatamodel.TrunkSta ? "images/TT/Open_door.png" : ""
                fillMode: Image.PreserveAspectFit
            }

            spacing: 14
        }

        Item {
            id: electricQuantityItem_Electric
            x: 1586
            y: 648
            width: 60
            height: 60

            Image {
                id: electricQuantity
                x: 0
                y: 0
                visible: !telltaledatamodel.BatSOCRptWarning
                source: "images/TT/ElectricQuantity.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: electricQuantityAlarm
                x: 0
                y: 0
                visible: telltaledatamodel.BatSOCRptWarning
                source: "images/TT/ElectricQuantityAlarm.png"
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

