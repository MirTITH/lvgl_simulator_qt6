import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import LCD

Window {
    width: 480 + 8
    height: 320 + 8
    visible: true
    title: qsTr("Lvgl Simulator")

    Rectangle {
        anchors.fill: parent
        border.width: 1

        LCD {
            id: lcd
            anchors.fill: parent
            anchors.margins: 4
            Component.onCompleted: {
                init(480, 320)
            }
        }
    }

    //    Text {
    //        anchors.fill: parent
    //        text: qsTr("text")
    //        function refreshText() {
    //            text = width.toString() + "x" + height.toString()
    //        }

    //        Component.onCompleted: {
    //            refreshText()
    //        }
    //        onWidthChanged: {
    //            refreshText()
    //        }
    //        onHeightChanged: {
    //            refreshText()
    //        }
    //    }
}
