import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick3D 1.15
import Quick3DAssets.SpeedMeter 1.0

Item {
    width: 546
    height: 546

    View3D {
        id: view3D
        width: 546
        height: 546
        SceneEnvironment {
            id: sceneEnvironment
            antialiasingMode: SceneEnvironment.MSAA
            antialiasingQuality: SceneEnvironment.High
        }
        Node {
            id: scene
            DirectionalLight {
                id: directionalLight
                brightness: 1
                ambientColor: "#f0f0f0"
            }
            PerspectiveCamera {
                id: camera
                z: 15
            }
            SpeedMeter {
                id: speedMeter
                speed: gaugedatamodel.HU_DisvehicleSpeed
            }
        }
        environment: sceneEnvironment
    }

    Image {
        id: left_line
        x: 0
        y: 0
        source: baseinfodatamodel.currentTheme ? "images/Gauge/LightTheme/left_line.png" : "images/Gauge/DarkTheme/left_line.png"
        fillMode: Image.PreserveAspectFit
    }

    Item {
        id: __materialLibrary__
    }
} //Item {//    id: item1//    width: 546//    height: 546//    Image {
//        id: left_line2
//        x: 0
//        y: 0
//        visible: true
//        source: "images/Gauge/left_line2.png"
//        fillMode: Image.PreserveAspectFit
//    }

//    Image {
//        id: speed_Bg2
//        x: 67
//        y: 8
//        visible: true
//        source: "images/Gauge/speed_Bg2.png"
//        clip: true
//        fillMode: Image.PreserveAspectFit

//        SpeedProgress {
//            id: speedProgress
//            visible: true
//            speedValue: gaugedatamodel.HU_DisvehicleSpeed
//        }
//    }

//    Item {
//        id: __materialLibrary__
//    }
//}


/*##^##
Designer {
    D{i:0;height:546;width:546}
}
##^##*/

