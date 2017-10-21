import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Window 2.2

Rectangle {
    id : root
    width: parent.width;
    height: parent.height

    signal relayClick
    property int  relayclickindex :  -1
    property bool relayon : false
    property real d_b: 2.54
    property real dpi: Screen.pixelDensity * d_b

    ListModel {
        id : main_model
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }
        ListElement {
            property string address: "192.168.1.25"
            port_number: "2000"
            name : ""
            timing : "定时关闭"
            property bool is_checked: false
        }


    }

    Component {
        id: contactDelegate

        Rectangle {
            id : delegate_rect
            width: root.width;
            height: 10 * dpi
            color : "#f0f0f0"

            Image {
                id: image
                x : 2 * dpi
                anchors.verticalCenter: parent.verticalCenter
                width: 7 * dpi
                height: 7 * dpi
                source: "/light.png"
            }

            Text {
                x : 10 * dpi
                y : 0.8 * dpi
                width: 20 * dpi
                text: address
                font.family: "Helvetica"
                font.pixelSize: 2 * dpi
                color: "#897870"
                visible: false
            }
            Text {
                x : 30 * dpi
                y : 0.8 * dpi
                width: 10 * dpi
                text: port_number
                font.family: "Helvetica"
                font.pixelSize: 2 * dpi
                color: "#897870"
                visible: false
            }

            Text {
                x : 10 * dpi
                y : 0.8 * dpi
                width: 10 * dpi
                text: "第" + (index+1) + "路"
                font.weight: Font.Bold
                font.family: "Helvetica"
                font.pixelSize: 3 * dpi
                color: "#666666"
            }
            Text {
                x : 20 * dpi
                y : 3 * dpi
                width: 20 * dpi
                text: timing
                font.family: "Helvetica"
                font.pixelSize: 2 * dpi
                color: "#897870"
                visible: false
            }
            Text {
                x : 10 * dpi
                y : 5 * dpi
                width: 20 * dpi
                text: name
                font.weight: Font.Bold
                font.family: "Helvetica"
                font.pixelSize: 2.5 * dpi
                color: "#888888"
            }

            Switch {
                id : button
                x : delegate_rect.width - 15 * dpi
                anchors.verticalCenter: parent.verticalCenter
                checked: is_checked

                MouseArea {
                    anchors.fill: parent;
                    onClicked: {
                        //main_model.setProperty(index, "is_checked", is_checked?false:true)
                        if(is_checked?false:true) {
                            console.log("set botton " + index + " on");
                        } else {
                            console.log("set botton " + index + " off");
                        }
                        relayclickindex = index
                        relayon = is_checked?false:true
                        relayClick();
                    }
                }
            }

            Rectangle {
                x : 0
                y : delegate_rect.height - 1
                width: root.width
                height: 1
                color : "#c8c7cc"
            }
        }
    }

    ListView {
        id : main_listview
        anchors.fill: parent
        model: main_model
        delegate: contactDelegate
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        focus: true
    }


    function set_relay_val(index,value) {
        //console.log("QML:set erlay val:"+index + " onoff:" + value);
        main_model.setProperty(index, "is_checked", value?true:false);
    }

    function set_ioout_name(name,index) {
        main_model.setProperty(index, "name", name);
    }


}
