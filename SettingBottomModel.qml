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
    signal discuss
    signal adddevice

    property real d : 10 * dpi
    property real a : (root.width - (4 * d)) / 5
    property real b : a + d

    ImageButton {
        id : imgswitch1
        x : b * 0 + a
        anchors.verticalCenter: parent.verticalCenter
        buttonsize: d
        imageup: "png/about_kde-256.png"
        imagedown: "png/about_kde-256.png"
        onMyclick: {
            //console.log("index:"+column.clickindex)
            root.connect();
        }
    }

    ImageButton {
        id : imgswitch2
        x : b * 1 + a
        anchors.verticalCenter: parent.verticalCenter
        buttonsize: d
        imageup: "png/configure-256.png"
        imagedown: "png/configure-256.png"
        onMyclick: {
            //console.log("index:"+column.clickindex)
            root.disconnect();
        }
    }

    ImageButton {
        id : imgswitch3
        x : b * 2 + a
        anchors.verticalCenter: parent.verticalCenter
        buttonsize: d
        imageup: "png/add_group-256.png"
        imagedown: "png/add_group-256.png"
        onMyclick: {
            //console.log("index:"+column.clickindex)
            root.discuss();
        }
    }

    ImageButton {
        id : imgswitch4
        x : b * 3 + a
        anchors.verticalCenter: parent.verticalCenter
        buttonsize: d
        imageup: "png/find-256.png"
        imagedown: "png/find-256.png"
        onMyclick: {
            //console.log("index:"+column.clickindex)
            root.adddevice();
        }
    }




}
