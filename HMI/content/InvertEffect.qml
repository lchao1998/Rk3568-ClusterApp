import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15

OpacityMask {
    id: invert
    width: m_target.width
    height: m_target.height
    transform: Scale {
        yScale: -1
        origin.y: m_target.height/2
    }
    source: m_target
    property variant m_target: none.none
    anchors.topMargin: 8
    anchors.horizontalCenter: speedDisplay.horizontalCenter
    maskSource: mask

    Rectangle {
        id: mask
        width: invert.width
        height: invert.height
        visible: false
        scale: -1
        gradient: Gradient {
            orientation: Gradient.Vertical

            GradientStop {
                position: 0.5
                color: "#00ffffff"
            }

            GradientStop {
                position: 1
                color: "#7f000000"
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
