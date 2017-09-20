import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Window 2.2

Rectangle {
    id : root
    width: parent.width;
    height: parent.height

    property real d_b: 1
    property real dpi: Screen.pixelDensity * d_b

    signal connect
    signal disconnect
    signal deldevice
    signal adddevice

    property real b : 0.8 * root.width / 4
    property real a : 0.2 * root.width / 5

    HWColorButton {
        x : (a + b) * 0 + a
        width: b
        height: 8 * dpi
        anchors.verticalCenter: parent.verticalCenter
        name :"连接"
        color_type: "green"
        onClick: {
            root.connect();
        }
    }

    HWColorButton {
        x : (a + b) * 1 + a
        width: b
        height: 8 * dpi
        anchors.verticalCenter: parent.verticalCenter
        name :"断开"
        color_type: "blue"
        onClick: {
            root.disconnect();
        }
    }

    HWColorButton {
        x : (a + b) * 2 + a
        width: b
        height: 8 * dpi
        anchors.verticalCenter: parent.verticalCenter
        name :"添加"
        color_type: "qing_se"
        onClick: {
            root.adddevice();
        }
    }

    HWColorButton {
        x : (a + b) * 3 + a
        width: b
        height: 8 * dpi
        anchors.verticalCenter: parent.verticalCenter
        name :"删除"
        color_type: "oringe"
        onClick: {
            root.deldevice();
        }
    }
}
