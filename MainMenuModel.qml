import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Window 2.2

Rectangle {
    id : root
    width: parent.width;
    height: parent.height
    property real d_b: 3
    property real dpi: Screen.pixelDensity * d_b

    signal settingSig

    Label {
        y : 4 * dpi
        anchors.horizontalCenter: parent.horizontalCenter
        text : "网络远程控制"
        font.weight: Font.Bold
        font.pixelSize: 3 * dpi
        color: "#ffffff"
    }

    Label {
        x : 2 * dpi
        y : 10 * dpi
        text : "设备名称:"
        font.weight: Font.Bold
        font.pixelSize: 2 * dpi
        color: "#ffffff"
    }
    Label {
        x : 13 * dpi
        y : 10 * dpi
        text : "--------"
        font.weight: Font.Bold
        font.pixelSize: 2 * dpi
        color: "#AAAAAA"
    }

    Label {
        x : root.width - 15 * dpi
        y : 10 * dpi
        text : "分组:"
        font.weight: Font.Bold
        font.pixelSize: 2 * dpi
        color: "#ffffff"
    }
    Label {
        x : root.width - 8 * dpi
        y : 10 * dpi
        text : "------"
        font.weight: Font.Bold
        font.pixelSize: 2 * dpi
        color: "#AAAAAA"
    }


    Label {
        x : root.width - 8 * dpi
        y : 5 * dpi
        text : "设置"
        font.weight: Font.Bold
        font.pixelSize: 3 * dpi
        color: "#ffffff"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                root.settingSig();
            }
        }
    }




}
