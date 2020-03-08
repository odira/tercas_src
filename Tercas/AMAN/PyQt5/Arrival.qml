import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11

ColumnLayout {
    id: root
    Layout.maximumWidth: 450
    Layout.fillHeight: true
    spacing: 0

    property string iataCode: "LHR"
    property color airportColor: "blue"

    Rectangle {
        height: text.height + 20
        Layout.fillWidth: true
        border.color: airportColor
        color: airportColor

        Text {
            id: text
            anchors.centerIn: parent
            font.bold: true
            font.pixelSize: 14
            color: "white"
            text: qsTr(iataCode +  " Queue")
        }

        RoundButton {
            height: parent.height + 1
            width: height
            anchors.top: parent.top
            anchors.right: parent.right
            radius: 0

            contentItem: Text {
                horizontalAlignment: Text.AlignHCenter
                font.bold: true
                font.pixelSize: 20
                text: "X"
            }
            background: Rectangle {
                border.width: 1
                border.color: root.airportColor
            }

            onClicked: {
                root.destroy()
            }
        }
    }

    Rectangle {
        Layout.fillWidth: true
        Layout.fillHeight: true
        border.color: airportColor
        color: "transparent"

        ListView {
            id: vkoList
            anchors.fill: parent
            anchors.margins: 3
            spacing: 3
            verticalLayoutDirection: ListView.BottomToTop
            clip: true

            footerPositioning: ListView.OverlayFooter
            footer: Column {
                z: 2

                GridLayout {
                width: vkoList.width
                height: 50
                columnSpacing: 3

                    TextField {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 30
                        background: Rectangle { color: airportColor }
                        color: "white"
                        text: qsTr("№")
                    }

                    TextField {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 100
                        horizontalAlignment: Qt.AlignHCenter
                        background: Rectangle { color: "lightyellow"; border.color: "grey" }
                        font.bold: true
                        color: airportColor
                        wrapMode: TextInput.WordWrap
                        text: "Flight\nNumber"
                    }

                    TextField {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 60
                        horizontalAlignment: Qt.AlignHCenter
                        background: Rectangle { color: "lightyellow"; border.color: "grey" }
                        font.bold: true
//                        color: airportColor
                        wrapMode: TextInput.WordWrap
                        text: "Queue\nType"
                    }

                    TextField {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 70
                        horizontalAlignment: Qt.AlignHCenter
                        wrapMode: TextInput.WordWrap
                        font.bold: true
                        text: "ARR\nTime"
                    }

                    TextField {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 60
                        horizontalAlignment: Qt.AlignHCenter
                        wrapMode: TextInput.WordWrap
                        text: qsTr("Ground\nSpeed")
                    }

                    TextField {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 60
                        horizontalAlignment: Qt.AlignHCenter
                        wrapMode: TextInput.WordWrap
                        text: qsTr("ACFT\nType")
                    }

                    TextField {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        horizontalAlignment: Qt.AlignHCenter
                    }
                } // GridLayout

                Rectangle {
                    width: vkoList.width
                    height: 5
                    color: "white"
                }

            } // Column

            model: queue.create_model(iataCode)

            section.property: "eta_utc_hour"
            section.criteria: ViewSection.FullString
            section.delegate: Rectangle {
                width: vkoList.width
//                height: childrenRect.height * 1.5
                height: 35
                z: 1
                color: "transparent"

                TextField {
                    height: 25
                    anchors.centerIn: parent
                    background: Rectangle { border.color: "black"; radius: 3 }
                    font.bold: true
                    font.pixelSize: 12
                    color: "black"
                    text: section + " : 00 UTC"
                }
            }

            delegate: GridLayout {
                width: vkoList.width
                height: 25
                columnSpacing: 3

                    TextField {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 30
                        background: Rectangle { color: airportColor }
                        color: "white"
                        text: index + 1
                    }

                    TextField {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 100
                        horizontalAlignment: model.queue_type === 'ARR' ? Qt.AlignLeft : Qt.AlignRight
                        background: Rectangle { color: "lightyellow"; border.color: "grey" }
                        font.bold: true
                        color: airportColor
                        text: model.flight_icao !== 'None' ? model.flight_icao : model.flight_iata
                    }

                    TextField {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 60
                        horizontalAlignment: Qt.AlignHCenter
                        background: Rectangle { color: "lightyellow"; border.color: "grey" }
                        color: model.queue_type === 'ARR' ? "black" : "brown"
                        text: model.queue_type
                    }

                    TextField {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 70
                        horizontalAlignment: Qt.AlignHCenter
                        font.bold: true
                        text: {
                            var datetime = new Date(model.eta_utc * 1000);
                            datetime.setHours(datetime.getUTCHours()); // Here we set hours to UTC
                            return Qt.formatTime(datetime, "hh : mm");
                        }
                    }

                    TextField {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 60
                        horizontalAlignment: Qt.AlignHCenter
                        text: model.ground_speed
                    }

                    TextField {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 60
                        horizontalAlignment: Qt.AlignHCenter
                        text: model.acft
                    }

                    TextField {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        horizontalAlignment: Qt.AlignHCenter
                    }
            }
        }
    }
}
