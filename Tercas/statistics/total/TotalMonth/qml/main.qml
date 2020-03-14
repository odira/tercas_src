import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQml.Models 2.12

import Wiipuri.Calendar 1.0
import Wiipuri.Models 1.0
import Wiipuri.Process 1.0

ApplicationWindow {
    id: rootWindow
    width: Screen.width
    height: Screen.height
    visible: true
    title: qsTr("Статистика загрузки секторов (по суткам)")

    Process { id: process }
    TotalMonthModel { id: totalMonthModel }

    header: RowLayout {
        Layout.fillWidth: true
        height: 80
    }

    property int numOfColumns: totalMonthModel.columnCount()
    property int space: 5
    property int sectorLabelWidth: 80
    property int loadLabelWidth: (rootWindow.width - space * 2 - sectorLabelWidth) / 12 - space
    property int labelHeight: 18

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
                border.color: "brown"
                Text {
                    anchors.centerIn: parent
                    font.bold: true
                    font.pixelSize: 12
                    text: qsTr("Год")
                }
            }
            Row {
                Layout.fillWidth: true
                height: parent.height
                spacing: space
                Repeater {
                    model: numOfColumns - 1
                    delegate: Rectangle {
                        width: loadLabelWidth
                        height: labelHeight
                        border.color: "green"
                        Text {
                            anchors.centerIn: parent
                            font.bold: true
                            font.pixelSize: 12
                            text: CalendarFunctions.getMonthName(index + 1)
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
            model: totalMonthModel

            delegate: Rectangle {
                id: rowDelegate
                width: listView.width
                height: 18

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
                            text: model.year
                        }
                    }
                    Row {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        spacing: space
                        Repeater {
                            model: numOfColumns

                            delegate: Rectangle {
                                width: loadLabelWidth
                                height: rowDelegate.height
                                border.color: loadText.text !== '0' ? "orange" : "transparent";

                                property int day: index + 1

                                Text {
                                    id: loadText
                                    anchors.centerIn: parent
                                    text: totalMonthModel.get(row, index) //feb
                                    visible: text !== '0'
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    footer: Row {
        id: footer
        width: parent.width
        anchors.right: parent.right
        anchors.rightMargin: 20
        height: header.height
        layoutDirection: Qt.RightToLeft
        spacing: 20

        Button {
            text: qsTr("Close")
            onClicked: Qt.quit()
        }
        Button {
            text: qsTr("Plot")
            onClicked: {
                var appPath = '/Users/tercas/Programming/src/Tercas/statistics/total/TotalMonth/py/plotTotalMonth.py'
                process.start(appPath)
            }
        }
    }
}
