import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Window 2.0


Item {

    id : root

    signal click

    property real d_b: 1
    property real dpi: Screen.pixelDensity * d_b

    property string color_type : "blue"
    property color button_press_color : "#66ac58"
    property color button_exit_color : "#6fb264"
    property color press_font_color : "#8ac182"
    property color exit_font_color : "#FFFFFF"
    property string name : "Button"

Rectangle {
    id : button
    width: root.width
    height: root.height
    radius: 1 * dpi
    color : "#73b666"
    border.color: button_press_color
    border.width: 2


    Component.onCompleted :
    {
        if(color_type == "blue") {
            button_press_color = "#66ac58"
            button_exit_color = "#6fb264"
            press_font_color = "#8ac182"
            exit_font_color = "#FFFFFF"
        } else if(color_type == "green") {
            button_press_color = "#497cb8"
            button_exit_color = "#5589c4"
            press_font_color = "#8fafd2"
            exit_font_color = "#FFFFFF"
        } else if(color_type == "qing_se") {
            button_press_color = "#5fb1cf"
            button_exit_color = "#75bdda"
            press_font_color = "#a8c8d5"
            exit_font_color = "#FFFFFF"
        } else if(color_type == "oringe") {
            button_press_color = "#e19e54"
            button_exit_color = "#e6af5f"
            press_font_color = "#d7c5b0"
            exit_font_color = "#FFFFFF"
        }
        animateColor.start()
        name_change_back.start()
        name_id.text = root.name
    }




    Text {
        id : name_id
        anchors.centerIn: button
        text: "关闭"
        color: "#FFFFFF"
        font.weight: Font.Bold
        font.family: "微软雅黑"
        font.pixelSize: button.height * 0.4
    }

    MouseArea
    {
        anchors.fill: parent
        onPressed:
        {
            animateColor1.start()
            name_change_to.start()
        }
        onExited:
        {
            animateColor.start()
            name_change_back.start()
        }
        onClicked: {
            root.click();
        }
    }

    PropertyAnimation
    {
        id : animateColor
        target: button
        properties: "color"
        to : button_exit_color
        duration: 100
    }
    PropertyAnimation
    {
        id : animateColor1
        target: button
        properties: "color"
        to : button_press_color
        duration: 100
    }

    PropertyAnimation
    {
        id : name_change_to
        target: name_id
        properties: "color"
        to : press_font_color
        duration: 100
    }
    PropertyAnimation
    {
        id : name_change_back
        target: name_id
        properties: "color"
        to : exit_font_color
        duration: 100
    }
}


}
