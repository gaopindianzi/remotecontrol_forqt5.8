import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Window 2.2

Rectangle {
    id : root
    width: parent.width;
    height: parent.height

    property real d_b: 3
    property real dpi: Screen.pixelDensity.toFixed(2) * d_b

    Label {
        x : 1 * dpi
        y : 1.8 * dpi
        text : "设备地址:"
        font.weight: Font.Bold
        font.pixelSize: 2 * dpi
        color: "#ffffff"
    }
    Label {
        x : 13 * dpi
        y : 1.8  * dpi
        text : "--------"
        font.weight: Font.Bold
        font.pixelSize: 2 * dpi
        color: "#AAAAAA"
    }

    Label {
        x : 1 * dpi
        y : 6 * dpi
        text : "输出数量:"
        font.weight: Font.Bold
        font.pixelSize: 2 * dpi
        color: "#ffffff"
    }
    Label {
        x : 13 * dpi
        y : 6 * dpi
        text : "--------"
        font.weight: Font.Bold
        font.pixelSize: 2 * dpi
        color: "#AAAAAA"
    }


    Label {
        x : root.width - 18 * dpi
        y : 6 * dpi
        text : "状态:"
        font.weight: Font.Bold
        font.pixelSize: 2 * dpi
        color: "#ffffff"
    }
    Label {
        x : root.width - 12 * dpi
        y : 6 * dpi
        text : "正在连续..."
        font.weight: Font.Bold
        font.pixelSize: 2 * dpi
        color: "#AAAAAA"
    }



}
