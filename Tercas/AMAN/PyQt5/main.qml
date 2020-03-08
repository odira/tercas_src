import QtQuick 2.11 // version 2.12 for PyQt5
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11 // version 1.12 for PyQt5


ApplicationWindow {
    id: appWindow
    visible: true
    visibility: Qt.WindowFullScreen
    title: qsTr("AMAN - Arrival Manager")
    color: "whitesmoke"

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            anchors.left: parent.left
            anchors.leftMargin: 10

            ToolButton {
                text: qsTr("VKO")
                background: Rectangle { border.color: "teal" }
                contentItem: Text { text: parent.text; color: "teal" }
                font.bold: true
                onClicked: {
                    var component = Qt.createComponent("Arrival.qml");
                    if (component.status === Component.Ready)
                        component.createObject(grid, { "iataCode" : "VKO", "airportColor" : "teal" });
                }
            }

            ToolButton {
                text: qsTr("DME")
                background: Rectangle { border.color: "brown" }
                contentItem: Text { text: parent.text; color: "brown" }
                font.bold: true
                onClicked: {
                    var component = Qt.createComponent("Arrival.qml");
                    if (component.status === Component.Ready)
                        component.createObject(grid, { "iataCode" : "DME", "airportColor" : "brown" });
                }
            }

            ToolButton {
                text: qsTr("SVO")
                background: Rectangle { border.color: "red" }
                contentItem: Text { text: parent.text; color: "red" }
                font.bold: true
                onClicked: {
                    var component = Qt.createComponent("Arrival.qml");
                    if (component.status === Component.Ready)
                        component.createObject(grid, { "iataCode" : "SVO", "airportColor" : "red" });
                }
            }

            ToolButton {
                text: qsTr("ZIA")
                background: Rectangle { border.color: "blue" }
                contentItem: Text { text: parent.text; color: "blue" }
                font.bold: true
                onClicked: {
                    var component = Qt.createComponent("Arrival.qml");
                    if (component.status === Component.Ready)
                        component.createObject(grid, { "iataCode" : "ZIA", "airportColor" : "blue" });
                }
            }

            Text {
                id: headerText
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 24
                font.bold: true
                text: "Calculating UTC time"

                Timer {
                    id: headerTimer
                    interval: 1000
                    running: true
                    repeat: true
                    onTriggered: {
                        var datetime = new Date();
                        datetime.setHours(datetime.getUTCHours()); // Here we set hours to UTC
                        headerText.text = Qt.formatTime(datetime, "hh : mm : ss UTC");
                    }
                }
            }
        }
    }


    Timer {
        id: timer
        interval: 10000
        running: true
        repeat: true
        onTriggered: queue.process_models();
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        GridLayout {
            id: grid
            Layout.fillWidth: true
            Layout.fillHeight: true
            columns: 4
            columnSpacing: 30
        }
    }


    footer: ColumnLayout {
        width: appWindow.width

        Rectangle {
            Layout.fillWidth: true
            height: 1
            color: "black"
        }

        DialogButtonBox {
            Layout.fillWidth: true
            alignment: Qt.AlignRight

            background: Rectangle {
                color: appWindow.color
            }

            RoundButton {
                id: quitButton
                width: 100
                radius: 5
                font.bold: true
                text: "Quit"
                onClicked: {
                    timer.running = false
                    Qt.quit()
                }
            }
        }
    }
}
