import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick3D 1.15
import Quick3DAssets.TachMeter 1.0

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

            TachMeter {
                id: tachMeter
                visible: true
                speed: gaugedatamodel.revSpeed
            }
        }
        environment: sceneEnvironment
    }

    Image {
        id: right_line
        x: 0
        y: 0
        source: baseinfodatamodel.currentTheme ? "images/Gauge/LightTheme/right_line.png" : "images/Gauge/DarkTheme/right_line.png"
        fillMode: Image.PreserveAspectFit
    }

    Item {
        id: __materialLibrary__
    }
}

/*##^##
Designer {
    D{i:0;height:546;width:546}D{i:4}D{i:6}
}
##^##*/

