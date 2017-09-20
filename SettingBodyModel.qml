import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Window 2.2

Rectangle {
    id : root
    width: parent.width;
    height: parent.height

    property real d_b: 1
    property real dpi: Screen.pixelDensity * d_b
    property int  radioindex : -1
    property string hostaddr : ""
    property string hostport : ""

    signal radioclick

    ListModel {
        id : modelval

        ListElement {
            address: "192.168.1.250"
            port_number: "2000"
            ischecked : false
        }

    }

    Component {
        id: deviceDelegate
        Rectangle {
            id : delegate_rect
            width: root.width;
            height: 8 * dpi
            color : "#f0f0f0"

            Image {
                id: image
                x : 3.54 * dpi
                anchors.verticalCenter: parent.verticalCenter
                width: 6 * dpi
                height: 6 * dpi
                source: "png/gohome-256.png"
            }

            Text {
                id : idaddr
                x : 10 * dpi
                anchors.verticalCenter: parent.verticalCenter
                width: 20 * dpi
                text: address
                font.family: "Helvetica"
                font.pixelSize: 3 * dpi
                color: "#897870"
            }

            Text {
                id : idport
                x : 32 * dpi
                anchors.verticalCenter: parent.verticalCenter
                width: 10 * dpi
                text: port_number
                font.family: "Helvetica"
                font.pixelSize: 3 * dpi
                color: "#897870"
            }

            Text {
                id : idindex
                x : 12 * dpi
                anchors.verticalCenter: parent.verticalCenter
                width: 10 * dpi
                text: "第" + (index+1) + "路"
                font.family: "Helvetica"
                font.pixelSize: 2.2 * dpi
                color: "#897870"
                visible: false
            }

            RadioButton {
                id : button
                x : delegate_rect.width - 12 * dpi
                checked: ischecked
                anchors.verticalCenter: parent.verticalCenter
                MouseArea {
                    anchors.fill: button
                    onClicked: {
                        var i
                        radioindex = index
                        for(i=0;i<modelval.count;i++) {
                            modelval.setProperty(i,"ischecked",false);
                        }
                        modelval.setProperty(index,"ischecked",true);
                        hostaddr = idaddr.text
                        hostport = idport.text
                        root.radioclick();
                        radioindex = index;
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
        anchors.fill: parent
        model: modelval
        delegate: deviceDelegate
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        focus: true
    }

    function append(address,port) {
        modelval.append({"address":address,"port_number":port,"ischecked":false})
    }

    function remove(index) {
        modelval.remove(index)
    }

    function clear() {
        modelval.clear();
    }

    function setselect(index) {
        console.log("select device:" + index)
        modelval.setProperty(index,"ischecked",true);
    }
}



