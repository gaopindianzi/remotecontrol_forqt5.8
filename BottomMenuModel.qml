import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Window 2.2

Rectangle {
    id : root
    width: parent.width;
    height: parent.height

    property real d_b: 2.54
    property real dpi: Screen.pixelDensity * d_b

    Label {
        x : 1 * dpi
        anchors.verticalCenter: root.verticalCenter
        text : "地址:"
        font.weight: Font.Bold
        font.family: "Helvetica"
        font.pixelSize: 2.4 * dpi
        color: "#ffffff"
    }
    Label {
        id : ipaddr
        x : 7 * dpi
        anchors.verticalCenter: root.verticalCenter
        text : "--------"
        font.weight: Font.Bold
        font.family: "Helvetica"
        font.pixelSize: 2.4 * dpi
        color: "#AAAAAA"
    }


    Label {
        x : root.width - 30 * dpi
        anchors.verticalCenter: root.verticalCenter
        text : "状态:"
        font.weight: Font.Bold
        font.family: "Helvetica"
        font.pixelSize: 2.4 * dpi
        color: "#ffffff"
    }
    Label {
        id : uistatus
        x : root.width - 24 * dpi
        anchors.verticalCenter: root.verticalCenter
        text : "正在连续..."
        font.weight: Font.Bold
        font.pixelSize: 2.4 * dpi
        color: "#AAAAAA"
    }

    Label {
        id : uidebug
        x : root.width - 38 * dpi
        anchors.verticalCenter: root.verticalCenter
        text : "debugmsg"
        font.weight: Font.Bold
        font.pixelSize: 2.4 * dpi
        font.wordSpacing: 0.01 * dpi
        color: "#AAAAAA"
        visible: false
    }

    function setstatus(msg) {
        uistatus.text = msg;
    }


    function setuidebug(msg) {
        uidebug.text = msg;
    }
    function setipinfo(info) {
        ipaddr.text = info;
    }

}
