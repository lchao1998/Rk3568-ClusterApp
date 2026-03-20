import QtQuick 2.15
import QtQuick3D 1.15
import QtQuick3D.Materials 1.14
import QtQuick3D.Materials 1.15

Node {
    id: rootNode
    property real speed: 0

    Node {
        id: tachSpeedMeter
        x: -1.1427
        y: 1.87
        eulerRotation.z: -21.19
        eulerRotation.y: -25.2
        eulerRotation.x: -20.77
        z: 0.63
        scale.z: 1


        Model {
            id: tachSpeedMeter_Bar_Bg
            visible: true
            source: "meshes/tachSpeedMeter_Bar.mesh"
            eulerRotation.z: 40
            materials: material__Bar_Bg
        }
        Model {
            id: tachSpeedMeter_Bg
            visible: true
            source: "meshes/tachSpeedMeter_Bg.mesh"
            materials: material_Bg
        }

        Model {
            id: tachSpeedMeter_Bar_Fg_Oil
            visible: false
            source: "meshes/tachSpeedMeter_Bar.mesh"
            materials: material__Bar_Fg
            eulerRotation.y: 0
            eulerRotation.x: 0
            eulerRotation.z: 40
        }

        Model {
            id: tachSpeedMeter_Bar_Fg_Electric
            visible: true
            source: "meshes/tachSpeedMeter_Bar.mesh"
            materials: customMaterial
            eulerRotation.z: 40
        }



    }

    Node {
        id: __materialLibrary__

        DefaultMaterial {
            id: material__Bar_Bg
            diffuseMap: texture2
            objectName: "material__26_material"
            diffuseColor: "#ffffff"

            Texture {
                id: texture2
                source: baseinfodatamodel.currentTheme ? "../../../content/images/Gauge/LightTheme/progress_Bg.png" : "../../../content/images/Gauge/DarkTheme/progress_Bg.png"
            }
        }

        DefaultMaterial {
            id: material_Bg
            diffuseMap: texture3
            objectName: "New Material"

            Texture {
                id: texture3
                source: baseinfodatamodel.currentTheme ? "../../../content/images/Gauge/LightTheme/TachSpeed_Bg.png" : "../../../content/images/Gauge/DarkTheme/TachSpeed_Bg.png"
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
                positionV: 0.8 - (rootNode.speed / 8) * 0.6
                tilingModeHorizontal: Texture.Repeat
            }
        }

        CustomMaterial {
            id: customMaterial
            passes: renderPass
            objectName: "New Material"

            property real blendIntensity: 1
            property TextureInput textureEnergyRecovery: textureEnergyRecovery
            property TextureInput textureDrivingPower_Blue: textureDrivingPower_Blue
            property TextureInput textureDrivingPower_Red: textureDrivingPower_Red
            property TextureInput texturePointer: texturePointer
            property real textureOffsetU: textureOffest.positionU
            property real textureOffsetV: textureOffest.positionV
            property real textureEnergyRecoveryOffsetU: energyRecovery.positionU
            property real textureEnergyRecoveryOffsetV: energyRecovery.positionV
            property real textureDrivingPower_BlueOffsetU: drivingPower_Blue.positionU
            property real textureDrivingPower_BlueOffsetV: drivingPower_Blue.positionV
            property real textureDrivingPower_RedOffsetU: drivingPower_Red.positionU
            property real textureDrivingPower_RedOffsetV: drivingPower_Red.positionV

            hasTransparency: true
            ShaderInfo {
                id: shaderInformation
                type: "GLSL"
                version: "330"
            }

            Pass {
                id: renderPass
                shaders: [vertShader, fragShader]
            }

            Shader {
                id: vertShader
                stage: Shader.Vertex
                shader: "qrc:/content/shaders/Textured_ELe.vert"
            }

            Shader {
                id: fragShader
                stage: Shader.Fragment
                shader: "qrc:/content/shaders/Textured_ELe.frag"
            }

            TextureInput {
                id: textureEnergyRecovery
                texture: energyRecovery
            }

            TextureInput {
                id: textureDrivingPower_Blue
                texture: drivingPower_Blue
            }

            TextureInput {
                id: textureDrivingPower_Red
                texture: drivingPower_Red
            }

            TextureInput {
                id: texturePointer
                texture: pointer_Fg
            }

            Texture {
                id: energyRecovery
                source: baseinfodatamodel.currentTheme ? "../../../content/images/Gauge/LightTheme/energyRecovery_Fg.png" : "../../../content/images/Gauge/DarkTheme/energyRecovery_Fg.png"
                positionV: gaugedatamodel.MotorPowerType ? (gaugedatamodel.MotorPower / 60) * 0.05 - 0.05 : -0.07
                tilingModeHorizontal: Texture.Repeat
            }


            Texture {
                id: drivingPower_Blue
                source: baseinfodatamodel.currentTheme ? "../../../content/images/Gauge/LightTheme/drivingPower_Fg_Blue.png" : "../../../content/images/Gauge/DarkTheme/drivingPower_Fg_Blue.png"
                positionV: gaugedatamodel.MotorPowerType ? 0.61 : (gaugedatamodel.MotorPower <= 183 ? 0.61 - (gaugedatamodel.MotorPower / 183) * 0.56 : 0.05)
                tilingModeHorizontal: Texture.ClampToEdge
            }

            Texture {
                id: drivingPower_Red
                source: baseinfodatamodel.currentTheme ? "../../../content/images/Gauge/LightTheme/drivingPower_Fg_Red.png" : "../../../content/images/Gauge/DarkTheme/drivingPower_Fg_Red.png"
                positionV:  (gaugedatamodel.MotorPowerType && gaugedatamodel.MotorPower <= 183) ? 0.13 : 0.1 - ((gaugedatamodel.MotorPower-183) / 17) * 0.05
                tilingModeHorizontal: Texture.ClampToEdge
            }


            Texture {
                id: pointer_Fg
                source: "../../../content/images/Gauge/pointer_Fg.png"
                tilingModeHorizontal: Texture.Repeat
            }

            Texture {
                id: textureOffest
                positionV: 0.16
            }






            shaderInfo: shaderInformation
        }

    }
}
