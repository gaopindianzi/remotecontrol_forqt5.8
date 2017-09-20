
import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import an.qt.ColorMaker 1.0
import an.qt.SignalRelaySocket 1.0
import QtQuick.Window 2.2



ApplicationWindow {
    visible: true
    width: 750 /2
    height: 1334/2
    title: qsTr("relay remote controler")

    property real d_b: 1
    property real dpi: Screen.pixelDensity * d_b

    property int height_a : 10.2 * dpi
    property int height_b : 3.5 * dpi
    property int settingline_a : 16 * dpi
    property int settingline_b : 12 * dpi

    SignalRelaySocket {
        id : relaysocket

        onDeviceStatusMsg: {
            console.log("QMLdebug:" + msg);
        }
        onUiStatus : {
            head_bar.setstatus(msg);
        }
        onUidebug: {
            console.log(msg);
            head_bar.setuidebug(msg);
        }
        onRelaychange: {
            body.set_relay_val(index,on);
        }
        onConnectedsig: {
            head_bar.setipinfo(addr);
        }
        onIoOutName: {
            body.set_ioout_name(name,index);
        }
        onDevName: {
            main_bar.set_device_name(name);
        }
        onDevGroup1Name: {
            main_bar.set_group_name(name);
        }

    }


    Component.onCompleted: {
        relaysocket.load_data();
        var i,count
        count = relaysocket.getcount();
        settinglist.clear();
        for(i=0;i<count;i++) {
            settinglist.append(relaysocket.getaddr(i),relaysocket.getport(i))
        }
        settinglist.setselect(relaysocket.get_last_host_index());
    }

    Component.onDestruction: {
        relaysocket.save_data();
    }

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

            onRelayClick: {
                relaysocket.revert_relay(body.relayclickindex);
            }

        }

        MainMenuModel {
            id : main_bar
            x : 0
            y : 0
            width: main_rect.width
            height: height_a
            color : "#336699"

            onSettingSig : {
                console.log("main setting click:" + dpi);
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
            id : settinglist
            x : 0
            y : settingline_a
            width: setting_rect.width
            height: setting_rect.height - settingline_a - settingline_b

            onRadioclick: {
                settinghead.sethostaddr(settinglist.hostaddr,settinglist.hostport)
                relaysocket.set_last_host_index(settinglist.radioindex);
            }

        }

        SettingHeadModel {
            id : settinghead
            x : 0
            y : 0
            width: main_rect.width
            height: settingline_a
            color : "#336699"
            onOnreturn : {
                console.log("main back click:" + dpi);
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
                relaysocket.connectdevide(settinglist.hostaddr, settinglist.hostport * 1)
                main_rect.x = 0
                setting_rect.x = parent.width
                head_bar.setipinfo(settinglist.hostaddr);
            }

            onDisconnect : {
                console.log("disconnect");
            }

            onDiscuss : {
                settinglist.append(settinghead.hostaddr,settinghead.hostport)
                relaysocket.add_addrs(settinghead.hostaddr,settinghead.hostport)
            }

            onAdddevice : {
                settinglist.remove(settinglist.radioindex)
                relaysocket.del_note(settinglist.radioindex);
                settinglist.radioindex = -1
            }

        }

        Behavior on x {
            NumberAnimation {
                duration: 300
            }
        }

    }
}













