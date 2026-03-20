import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick3D 1.15

ShaderEffect {
    id: speedProgress

    property real speedValue: 0

    property variant source: sourceImage
    width: 438
    height: 438

    vertexShader: "
          uniform highp mat4 qt_Matrix;
          attribute highp vec4 qt_Vertex;
          attribute highp vec2 qt_MultiTexCoord0;
          varying highp vec2 texcoord;

          void main() {
          texcoord=qt_MultiTexCoord0;
          gl_Position = qt_Matrix * qt_Vertex;
          }
          "
    fragmentShader: "
          #define M_PI 3.141592653589793
          varying highp vec2 texcoord;
          uniform sampler2D source;
          uniform float qt_Opacity;
          uniform lowp float speedValue;

          //Rotation matrix
          mat2 rotate2d(float _angle){
          float angle = radians(_angle);
          return mat2(cos(angle),sin(angle),
                         -sin(angle),cos(angle));
           }

          void main() {
          vec2 uv = texcoord - vec2(0.5, 0.5);

          float angle = atan(uv.x, uv.y) / (2.0 * M_PI);
          float v = 0.1 - 0.52 * speedValue / 220.0;

          vec4 color = texture2D(source, texcoord);

          color = mix(color, vec4(0.0), step(angle,v));

          gl_FragColor = color * qt_Opacity;

          }
          "

    Image {
        id: sourceImage
        x: 0
        y: 0
        visible: false
        source: "images/Gauge/progress.png"
        fillMode: Image.PreserveAspectFit
    }

    Item {
        id: __materialLibrary__
    }

}

/*##^##
Designer {
    D{i:0;height:438;width:438}
}
##^##*/
