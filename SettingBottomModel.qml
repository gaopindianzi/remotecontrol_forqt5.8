import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Window 2.2

Rectangle {
    id : root
    width: parent.width;
    height: parent.height

    property real d_b: 2.54
    property real dpi: Screen.pixelDensity * d_b

    signal connect
    signal disconnect
    signal discuss
    signal adddevice


    ImageButton {
        id : imgswitch1
        x : root.width * 1 / 5 - 4 * dpi
        anchors.verticalCenter: parent.verticalCenter
        buttonsize: 8 * dpi
        imageup: "png/about_kde-256.png"
        imagedown: "png/about_kde-256.png"
        onMyclick: {
            //console.log("index:"+column.clickindex)
            root.connect();
        }
    }

    ImageButton {
        id : imgswitch2
        x : root.width * 2 / 5 - 4 * dpi
        anchors.verticalCenter: parent.verticalCenter
        buttonsize: 8 * dpi
        imageup: "png/configure-256.png"
        imagedown: "png/configure-256.png"
        onMyclick: {
            //console.log("index:"+column.clickindex)
            root.disconnect();
        }
    }

    ImageButton {
        id : imgswitch3
        x : root.width * 3 / 5 - 4 * dpi
        anchors.verticalCenter: parent.verticalCenter
        buttonsize: 8 * dpi
        imageup: "png/add_group-256.png"
        imagedown: "png/add_group-256.png"
        onMyclick: {
            //console.log("index:"+column.clickindex)
            root.discuss();
        }
    }

    ImageButton {
        id : imgswitch4
        x : root.width * 4 / 5 - 4 * dpi
        anchors.verticalCenter: parent.verticalCenter
        buttonsize: 8 * dpi
        imageup: "png/find-256.png"
        imagedown: "png/find-256.png"
        onMyclick: {
            //console.log("index:"+column.clickindex)
            root.adddevice();
        }
    }


}
