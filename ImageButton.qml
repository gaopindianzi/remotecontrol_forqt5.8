import QtQuick 2.0

Item {
    id : root
    property url imageup;
    property url imagedown;
    property real buttonsize;
    property color arccolor : "#aaaaaa"
    signal myclick
    width: buttonsize
    height: buttonsize

    property real r : root.width * 0.6

    Image {
        id: image
        width: r
        height: r
        anchors.centerIn: root
        source: root.imageup
    }

    Canvas {
        id : canvas
        anchors.centerIn: root
        width: root.width
        height: root.height

        onPaint: {
            var ctx = getContext("2d");
            ctx.lineWidth = 1
            ctx.strokeStyle = root.arccolor;
            ctx.arc(root.width/2,root.height/2,root.width/2-2,0,Math.PI*2);
            ctx.stroke();
        }
    }

    MouseArea {
        hoverEnabled : true
        anchors.fill: root
        onClicked: {
            root.myclick();
        }
        onEntered: {
            image.source = root.imagedown;
            root.arccolor = "#ffffff";
            canvas.requestPaint();
        }
        onExited: {
            image.source = root.imageup;
            root.arccolor = "#aaaaaa";
            canvas.requestPaint();
        }
    }
}
