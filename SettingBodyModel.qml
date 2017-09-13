import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Window 2.2

Rectangle {
    id : root
    width: parent.width;
    height: parent.height

    property real d_b: 2.54
    property real dpi: Screen.pixelDensity * d_b

    Component {
        id: deviceDelegate
        Rectangle {
            id : delegate_rect
            width: root.width;
            height: 6.4 * dpi
            color : "#f0f0f0"

            Image {
                id: image
                x : 3.54 * dpi
                anchors.verticalCenter: parent.verticalCenter
                width: 5 * dpi
                height: 5 * dpi
                source: "png/gohome-256.png"
            }

            Text {
                x : 12 * dpi
                y : 0.8 * dpi
                width: 20 * dpi
                text: address
                font.family: "Helvetica"
                font.pixelSize: 2.2 * dpi
                color: "#897870"
            }
            Text {
                x : 30 * dpi
                y : 0.8 * dpi
                width: 10 * dpi
                text: port_number
                font.family: "Helvetica"
                font.pixelSize: 2.2 * dpi
                color: "#897870"
            }

            Switch {
                id : button
                x : delegate_rect.width - 10 * dpi
                anchors.verticalCenter: parent.verticalCenter
            }

            Rectangle {
                x : 0
                y : delegate_rect.height - 1
                width: root.width
                height: 1
                color : "#c8c7cc"
            }
        }
    }


    ListView {
        anchors.fill: parent
        model: ContactDeviceSettingModel {}
        delegate: deviceDelegate
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        focus: true
    }

}
