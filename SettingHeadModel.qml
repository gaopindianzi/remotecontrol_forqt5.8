import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3

Rectangle {
    id : root
    width: parent.width;
    height: parent.height

    property real d_b: 2.54
    property real dpi: Screen.pixelDensity * d_b
    property string hostaddr : host_address.text
    property string hostport : host_port.text


    signal onreturn

    Label {
        anchors.horizontalCenter: parent.horizontalCenter
        y : 2 * dpi
        text : "设备管理"
        font.weight: Font.Bold
        font.pixelSize: 3 * dpi
        color: "#ffffff"
    }


    Image {
        id: image
        x : 1.5 * dpi
        y : 3 * dpi
        width: 5 * dpi
        height: 5 * dpi
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
        y : 9.5 * dpi
        text : "地址"
        font.weight: Font.Bold
        font.family: "Helvetica"
        font.pixelSize: 2.4 * dpi
        color: "#ffffff"
    }

    TextField {
        id: host_address
        x : 9 * dpi
        y : 9 * dpi
        width: root.width - 22 * dpi
        height: 5 * dpi
        font.pixelSize: 2.2 * dpi
        font.weight: Font.Bold
        font.family: "Helvetica"
        placeholderText: qsTr("address")
    }

    TextField {
        id: host_port
        x : root.width - 12 * dpi
        y : 9 * dpi
        width: 10 * dpi
        height: 5 * dpi
        font.pixelSize: 2.2 * dpi
        font.weight: Font.Bold
        font.family: "Helvetica"
        placeholderText: qsTr("port")
    }

    function sethostaddr(host,port) {
        host_address.text = host
        host_port.text = port
    }


}
