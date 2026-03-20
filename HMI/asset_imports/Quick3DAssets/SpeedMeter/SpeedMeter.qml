import QtQuick 2.15
import QtQuick3D 1.15

Node {
    id: rootNode
    property int speed: 0

    Node {
        id: speedMeter
        x: 1.10847
        y: 1.95
        z: 0.7
        eulerRotation.x: -21.82
        eulerRotation.y: 22.73
        eulerRotation.z: 30.87
        scale.y: 1

        Model {
            id: speedMeter_Bar_Bg
            source: "meshes/speedMeter_Bar.mesh"
            eulerRotation.z: -40
            materials: material__Bar_Bg
        }

        Model {
            id: speedMeter_Bg
            visible: true
            source: "meshes/speedMeter_Bg.mesh"
            materials: material__Fg
        }

        Model {
            id: speedMeter_Bar_Fg
            source: "meshes/speedMeter_Bar.mesh"
            materials: [
                        material__Bar_Fg
                    ]
            eulerRotation.z: -40
        }
    }

    Node {
        id: __materialLibrary__

        DefaultMaterial {
            id: material__Bar_Bg
            diffuseMap: texture2
            objectName: "New Material"

            Texture {
                id: texture2
                source: baseinfodatamodel.currentTheme ? "../../../content/images/Gauge/LightTheme/progress_Bg.png" : "../../../content/images/Gauge/DarkTheme/progress_Bg.png"
            }
        }

        DefaultMaterial {
            id: material__Fg
            diffuseMap: texture3
            objectName: "New Material"

            Texture {
                id: texture3
                source: baseinfodatamodel.currentTheme ? "../../../content/images/Gauge/LightTheme/speed_Bg.png" : "../../../content/images/Gauge/DarkTheme/speed_Bg.png"
            }
        }
        DefaultMaterial {
            id: material__Bar_Fg
            diffuseMap: texture1
            objectName: "material__27_material"
            diffuseColor: "#ffffff"

            Texture {
                id: texture1
                source: baseinfodatamodel.currentTheme ? "../../../content/images/Gauge/LightTheme/progress_Fg.png" : "../../../content/images/Gauge/DarkTheme/progress_Fg.png"
                positionV: 0.8 - (rootNode.speed / 150) * 0.6
                tilingModeHorizontal: Texture.Repeat
                Behavior on positionV {
                    SmoothedAnimation{velocity: 1.6}
                }
            }
        }
    }
}
