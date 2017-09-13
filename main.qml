import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import an.qt.ColorMaker 1.0
import an.qt.SignalRelaySocket 1.0
import QtQuick.Window 2.2



ApplicationWindow {
    visible: true
    width: 750/2
    height: 1334/2
    title: qsTr("Hello World")

    property real d_b: 3
    property real dpi: Screen.pixelDensity * d_b

    property int height_a : 14 * dpi
    property int height_b : 10 * dpi
    property int settingline_a : 14 * dpi
    property int settingline_b : 10 * dpi

    Rectangle {
        id : main_rect
        x : 0
        y : 0
        width: parent.width
        height: parent.height
        color: "#336699"

        BodyListView {
            id : body
            x : 0
            y : height_a
            width: main_rect.width
            height: main_rect.height - height_b - height_a
        }

        MainMenuModel {
            id : main_bar
            x : 0
            y : 0
            width: main_rect.width
            height: height_a
            color : "#336699"

            onSettingSig : {
                console.log("main setting click");
                main_rect.x = -parent.width
                setting_rect.x = 0
            }
        }


        BottomMenuModel {
            id : head_bar
            x : 0
            y : main_rect.height - height_b
            width: main_rect.width
            height: height_b
            color : "#336699"
        }

        Behavior on x {
            NumberAnimation {
                duration: 300
            }
        }
    }

    Rectangle {
        id : setting_rect
        x : parent.width
        y : 0
        width: parent.width
        height: parent.height
        color: "#336699"

        SettingBodyModel {
            x : 0
            y : settingline_a
            width: setting_rect.width
            height: setting_rect.height - settingline_a - settingline_b
        }

        SettingHeadModel {
            x : 0
            y : 0
            width: main_rect.width
            height: settingline_a
            color : "#336699"
            onOnreturn : {
                console.log("main back click");
                main_rect.x = 0
                setting_rect.x = parent.width
            }
        }

        SettingBottomModel {
            x : 0
            y : setting_rect.height - settingline_b
            width: main_rect.width
            height: settingline_b
            color : "#336699"

            onConnect : {
                console.log("connect");
            }

            onDisconnect : {
                console.log("disconnect");
            }

            onDiscuss : {
                console.log("diss");
            }

            onAdddevice : {
                console.log("add");
            }

        }

        Behavior on x {
            NumberAnimation {
                duration: 300
            }
        }

    }


    /*
    Rectangle {
        id : main_rect
        x : 0
        y : 0

        width: parent.width
        height: parent.height

        SignalRelaySocket {
            id : relaysocket
        }

        Column {
            Text {
                id: timeLabel;
                text:"hello,word!";


                font.pixelSize: 26;
            }

            Row {
                Button {
                    id : connect
                    text:"connect";
                    font.pixelSize: 26;
                    onClicked: {
                        relaysocket.connectdevide("192.168.1.150",2000);
                        sys_status.text = "start connect...";
                    }
                }

                Button {
                    id : close
                    text:"close";
                    font.pixelSize: 26;
                    onClicked: {
                        relaysocket.close();
                    }
                }

                Button {
                    id : trig_y1
                    text:"Y1";
                    font.pixelSize: 26;
                    onClicked: {
                        relaysocket.revert_relay(1);
                    }
                }
            }


            Text {
                id: sys_status;
                text:"status!";
                font.pixelSize: 26;
            }

            Connections {
                target: relaysocket;
                onDeviceStatusMsg:{
                    sys_status.text = msg;
                }
            }
        }



    }
    */


    /*


    Rectangle {
        id : main_rect
        x : 0
        y : 0

        width: 360;
        height: 360;
        Text {
            id: timeLabel;
            anchors.left: parent.left;
            anchors.leftMargin: 4;
            anchors.top: parent.top;
            anchors.topMargin: 4;
            font.pixelSize: 26;
        }
        ColorMaker {
            id: colorMaker;
            //color: Qt.green;
        }

        Rectangle {
            id: colorRect;
            anchors.centerIn: parent;
            width: 200;
            height: 200;
            color: "blue";
        }

        Button {
            id: start;
            text: "start";
            anchors.left: parent.left;
            anchors.leftMargin: 4;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: 4;
            onClicked: {
                colorMaker.start();
            }
        }
        Button {
            id: stop;
            text: "stop";
            anchors.left: start.right;
            anchors.leftMargin: 4;
            anchors.bottom: start.bottom;
            onClicked: {
                colorMaker.stop();
            }
        }



        function changeAlgorithm(button, algorithm){
            switch(algorithm)
            {
            case 0:
                button.text = "RandomRGB";
                break;
            case 1:
                button.text = "RandomRed";
                break;
            case 2:
                button.text = "RandomGreen";
                break;
            case 3:
                button.text = "RandomBlue";
                break;
            case 4:
                button.text = "LinearIncrease";
                break;
            }
        }

        Button {
            id: colorAlgorithm;
            text: "RandomRGB";
            anchors.left: stop.right;
            anchors.leftMargin: 4;
            anchors.bottom: start.bottom;
            onClicked: {
                var algorithm = (colorMaker.algorithm() + 1) % 5;
                main_rect.changeAlgorithm(colorAlgorithm, algorithm);
                colorMaker.setAlgorithm(algorithm);
            }
        }

        Button {
            id: quit;
            text: "quit";
            anchors.left: colorAlgorithm.right;
            anchors.leftMargin: 4;
            anchors.bottom: start.bottom;
            onClicked: {
                Qt.quit();
            }
        }

        Component.onCompleted: {
            colorMaker.color = Qt.rgba(0,180,120, 255);
            colorMaker.setAlgorithm(ColorMaker.LinearIncrease);
            changeAlgorithm(colorAlgorithm, colorMaker.algorithm());
        }

        Connections {
            target: colorMaker;
            onCurrentTime:{
                console.log("on time");
                //timeLabel.text = strTime;
                //timeLabel.color = colorMaker.timeColor;
            }
        }

        Connections {
            target: colorMaker;
            onColorChanged:{
                console.log("on color");
                //colorRect.color = color;
            }
        }
    }

    */



    /*


    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1 {
        }

        Page {
            Label {
                text: qsTr("Second page")
                anchors.centerIn: parent
            }
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("First")
        }
        TabButton {
            text: qsTr("Second")
        }
    }

    */
}
