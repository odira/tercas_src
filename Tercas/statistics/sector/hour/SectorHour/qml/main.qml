import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Window 2.11

import Wiipuri.Calendar 1.0

ApplicationWindow {
    id: root
    title: qsTr("Статистика МЦ АУВД По Часам")
    visible: true
    width: Screen.width
    height: Screen.height

    header: RowLayout {
        Layout.fillWidth: true
        height: 80

        DatePicker {
            Layout.alignment: Qt.AlignHCenter
            pickerDate: hourSectorModel.date
            onPickerDateUpdated: {
                hourSectorModel.setDate(pickerDate)
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 5

        ListView {
            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            snapMode: ListView.SnapToItem
            clip: true
            spacing: 2

            headerPositioning: ListView.OverlayHeader
            header: Rectangle {
                width: listView.width
                height: 72
                z: 2 // to overlay the header

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 5
                    spacing: 2

                    RowLayout {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        spacing: 2

                        Rectangle {
                            width: 150
                            Layout.fillHeight: true
                            color: "#582A20"
                            Text {
                                anchors.centerIn: parent
                                font.bold: true
                                color: "white"
                                text: qsTr("Смена")
                            }
                        }
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.fillHeight: true

                            Grid {
                                anchors.fill: parent
                                columns: 4
                                spacing: 2

                                Rectangle {
                                    width: parent.width / 24 * 5 - 1; height: parent.height; color: "#BE7052"
                                    Text {
                                        anchors.centerIn: parent
                                        textFormat: Text.RichText
                                        text: {
                                            terkasDate.date = hourSectorModel.date;
                                            return qsTr("Смена № <b>") + terkasDate.nightShift() + "</b>";
                                        }
                                    }
                                }
                                Rectangle {
                                    width: parent.width / 24 * 7 - 2; height: parent.height; color: "#F1DED1"
                                    Text {
                                        anchors.centerIn: parent
                                        textFormat: Text.RichText
                                        text: {
                                            terkasDate.date = hourSectorModel.date;
                                            return qsTr("Смена № <b>") + terkasDate.morningShift() + "</b>";
                                        }
                                    }
                                }
                                Rectangle {
                                    width: parent.width / 24 * 7 - 2; height: parent.height; color: "#F2C083"
                                    Text {
                                        anchors.centerIn: parent
                                        textFormat: Text.RichText
                                        text: {
                                            terkasDate.date = hourSectorModel.date;
                                            return qsTr("Смена № <b>") + terkasDate.daylightShift() + "</b>";
                                        }
                                    }
                                }
                                Rectangle {
                                    width: parent.width / 24 * 5 - 1; height: parent.height; color: "#9499A6"
                                    Text {
                                        anchors.centerIn: parent
                                        textFormat: Text.RichText
                                        text: {
                                            terkasDate.date = hourSectorModel.date;
                                            return qsTr("Смена № <b>") + terkasDate.eveningShift() + "</b>";
                                        }
                                    }
                                }
                            }
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 2
                        Rectangle {
                            width: 150
                            Layout.fillHeight: true
                            color: "#74593D"
                            Text {
                                anchors.centerIn: parent
                                font.bold: true
                                color: "white"
                                text: qsTr("Сектор")
                            }
                        }
                        Repeater {
                            model: 24
                            Rectangle {
                                id: hour
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                color: "#DCD9C6"
                                Text {
                                    anchors.centerIn: parent
                                    font.bold: true
                                    font.pixelSize: 10
                                    text: modelData + " - " + (modelData + 1)
                                }
                            }
                        }
                    }
                }
            }

            model: hourSectorModel
            delegate: Rectangle {
                id: rowDelegate
                property int currentIndex: index
                width: listView.width
                height: 20

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 5
                    anchors.rightMargin: 5
                    spacing: 2

                    Rectangle {
                        width: 150
                        Layout.fillHeight: true
                        color: "#B5C1B4"
                        Text {
                            anchors.centerIn: parent
                            font.bold: true
                            font.pixelSize: 11
                            text: hourSectorModel.getSectorLabel(index)
                        }
                    }
                    Repeater {
                        model: 24
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            property int rowNum: rowDelegate.currentIndex
                            color: hourSectorModel.getSectorColor(rowNum, index + 1)
                            Text {
                                id: label
                                anchors.centerIn: parent
                                font.pixelSize: 9
                                text: {
                                    var val = hourSectorModel.getSectorValue(rowNum, index + 1)
                                    return (val === undefined) ? "" : val
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
