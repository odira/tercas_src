import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12

import Wiipuri.Calendar 1.0

ApplicationWindow {
    id: rootWindow
    width: Screen.width
    height: Screen.height
    visible: true
    title: qsTr("Статистика загрузки секторов (по суткам)")

    header: RowLayout {
        Layout.fillWidth: true
        height: 80

        DatePicker {
            Layout.alignment: Qt.AlignHCenter
            showDate: false
            pickerDate: sectorDateModel.date
            onPickerDateUpdated: {
                sectorDateModel.setDate(pickerDate)
            }
        }
    }

    property int numOfDays: sectorDateModel.columnCount()
    property int space: 5
    property int sectorLabelWidth: 80
    property int loadLabelWidth: (rootWindow.width - sectorLabelWidth) / numOfDays - space
    property int labelHeight: 20

    ColumnLayout {
        id: mainContent
        anchors.fill: parent
        anchors.margins: space
        spacing: space

        RowLayout {
            Layout.fillWidth: true
            height: labelHeight
            Rectangle {
                id: sectorLabel
                width: sectorLabelWidth
                height: parent.height
                border.color: "yellow"
                Text {
                    anchors.centerIn: parent
                    font.bold: true
                    font.pixelSize: 12
                    text: qsTr("Сектор")
                }
            }
            Row {
                Layout.fillWidth: true
                height: parent.height
                spacing: space
                Repeater {
                    model: numOfDays
                    delegate: Rectangle {
                        width: loadLabelWidth
                        height: labelHeight
                        border.color: "green"
                        Text {
                            anchors.centerIn: parent
                            font.bold: true
                            font.pixelSize: 12
                            text: index + 1
                        }
                    }
                }
            }
        }

        ListView {
            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            snapMode: ListView.SnapToItem
            clip: true
            spacing: space
            model: sectorDateModel

            delegate: Rectangle {
                id: rowDelegate
                width: listView.width
                height: 20

                property int row: index

                RowLayout {
                    anchors.fill: parent
                    spacing: space
                    Rectangle {
                        width: sectorLabelWidth
                        Layout.fillHeight: true
                        border.color: "yellow"
                        Text {
                            anchors.centerIn: parent
                            font.bold: true
                            font.pixelSize: 11
                            text: sectorDateModel.getSectorLabel(row)
                        }
                    }
                    Row {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        spacing: space
                        Repeater {
                            model: numOfDays

                            delegate: Rectangle {
                                width: loadLabelWidth
                                height: rowDelegate.height
                                border.color: loadText.text !== '0' ? "orange" : "transparent";

                                property int day: index + 1

                                Text {
                                    id: loadText
                                    anchors.centerIn: parent
                                    text: sectorDateModel.getSectorLoad(rowDelegate.row, day)
                                    visible: text !== '0'
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
