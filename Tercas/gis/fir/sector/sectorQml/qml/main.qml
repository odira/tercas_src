import QtQuick 2.9
import QtQuick.Controls 2.2
//import QtQuick.Layouts 1.3
//import QtQuick.Window 2.0

ApplicationWindow {
    visible: true
    width: 960
    height: 480
//    width: Screen.width
//    height: Screen.height
//    title: qsTr("Hello World")

    StackView {
        anchors.fill: parent
        initialItem: ListPage { }
    }
}
