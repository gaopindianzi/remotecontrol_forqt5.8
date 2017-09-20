import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Window 2.2

Rectangle {
    id : root
    width: parent.width;
    height: parent.height
    property real d_b: 1
    property real dpi: Screen.pixelDensity * d_b

    signal settingSig

    Label {
        y : 1.6 * dpi
        anchors.horizontalCenter: parent.horizontalCenter
        text : "网络远程控制"
        font.weight: Font.Black
        font.family: "Helvetica"
        font.pixelSize: 3 * dpi
        color: "#ffffff"
    }

    Label {
        x : 2 * dpi
        y : 7 * dpi
        text : "设备名称:"
        font.weight: Font.Bold
        font.family: "Helvetica"
        font.pixelSize: 2.4 * dpi
        color: "#ffffff"
    }
    Label {
        id: device_name;
        x : 14 * dpi
        y : 7 * dpi
        text : ""
        font.weight: Font.Bold
        font.family: "Helvetica"
        font.pixelSize: 2.4 * dpi
        color: "#AAAAAA"
    }

    Label {
        x : root.width - 20 * dpi
        y : 7 * dpi
        text : "分组:"
        font.weight: Font.Bold
        font.family: "Helvetica"
        font.pixelSize: 2.4 * dpi
        color: "#ffffff"
    }
    Label {
        id : group_name_id
        x : root.width - 13 * dpi
        y : 7 * dpi
        text : ""
        font.weight: Font.Bold
        font.pixelSize: 2.4 * dpi
        color: "#AAAAAA"
    }


    Label {
        x : root.width - 8 * dpi
        y : 3.2 * dpi
        text : "设置"
        font.weight: Font.Bold
        font.family: "Helvetica"
        font.pixelSize: 2.6 * dpi
        color: "#ffffff"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                root.settingSig();
            }
        }
    }


    function set_device_name(name) {
        device_name.text = name;
    }

    function set_group_name(name) {
        group_name_id.text = name;
    }



}
