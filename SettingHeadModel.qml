import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Window 2.2

Rectangle {
    id : root
    width: parent.width;
    height: parent.height

    property real d_b: 2.54
    property real dpi: Screen.pixelDensity * d_b

    signal onreturn

    Image {
        id: image
        x : 1.5 * dpi
        y : 4.5 * dpi
        width: 6 * dpi
        height: 6 * dpi
        source: "/back-256.png"

        MouseArea {
            anchors.fill: parent
            onClicked: {
                root.onreturn();
            }
        }
    }

    Label {
        x : 2.5 * dpi
        y : 11.5 * dpi
        text : "地址"
        font.weight: Font.Bold
        font.pixelSize: 2.5 * dpi
        color: "#ffffff"
    }

    TextField {
        id: host_address
        x : 11 * dpi
        y : 11.4 * dpi
        width: 22 * dpi
        height: 3 * dpi
        font.pixelSize: 2.5 * dpi
        placeholderText: qsTr("address")
    }

    TextField {
        id: host_port
        x : 36 * dpi
        y : 11.4 * dpi
        width: 12 * dpi
        height: 3 * dpi
        font.pixelSize: 2.5 * dpi
        placeholderText: qsTr("port")
    }



    Label {
        anchors.horizontalCenter: parent.horizontalCenter
        y : 4.7244 * dpi
        text : "设备管理"
        font.weight: Font.Bold
        font.pixelSize: 3.5433 * dpi
        color: "#ffffff"
    }


}
