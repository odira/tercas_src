import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import Wiipuri.Models 1.0
import Wiipuri.Calendar 1.0

Component {
    Package {
        id: pack

        Item { id: gridItem; Package.name: 'grid'; width: grid.cellWidth; height: grid.cellHeight }
        Item { id: browserItem; Package.name: 'browser'; width: browser.width; height: browser.height }

        property int monthIndex: index

        property int headerFontSize: 14
        property int cellFontSize: 8

        Item {
            id: delegateItem

            ColumnLayout {
                id: rect
                anchors.fill: parent
                anchors.margins: 20

                Label {
                    Layout.fillWidth: true
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    font { bold: true; pixelSize: headerFontSize }
                    background: Rectangle { color: "orange"; radius: 1 }
                    text: CalendarFunctions.getMonthName0(monthIndex)
                }

                ListView {
                    id: listView
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    clip: true
                    model: SectorMonthDetailsModel {
                        year: root.year
                        month: monthIndex + 1
                    }
                    header: RowLayout {
                        width: listView.width
                        height: listView.height / 30
                        Label {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            horizontalAlignment: Qt.AlignHCenter
                            verticalAlignment: Qt.AlignVCenter
                            background: Rectangle { color: "white" }
                            font { pixelSize: cellFontSize; bold: true }
                            text: qsTr('Сектор')
                        }
                        Label {
                            Layout.preferredWidth: listView.width / 15 * 3
                            Layout.fillHeight: true
                            horizontalAlignment: Qt.AlignHCenter
                            verticalAlignment: Qt.AlignVCenter
                            background: Rectangle { color: "white" }
                            font { pixelSize: cellFontSize; bold: true }
                            text: qsTr('TOTAL')
                        }
                        Label {
                            Layout.preferredWidth: listView.width / 15 * 3
                            Layout.fillHeight: true
                            horizontalAlignment: Qt.AlignHCenter
                            verticalAlignment: Qt.AlignVCenter
                            background: Rectangle { color: "white" }
                            font { pixelSize: cellFontSize; bold: true }
                            text: qsTr('MAX')
                        }
                        Label {
                            Layout.preferredWidth: listView.width / 15 * 3
                            Layout.fillHeight: true
                            horizontalAlignment: Qt.AlignHCenter
                            verticalAlignment: Qt.AlignVCenter
                            background: Rectangle { color: "white" }
                            font { pixelSize: cellFontSize; bold: true }
                            text: qsTr('AVG')
                        }
                    }

                    delegate: Rectangle {
                        width: listView.width
                        height: listView.height / 34
                        RowLayout {
                            anchors.fill: parent
                            Label {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                horizontalAlignment: Qt.AlignHCenter
                                verticalAlignment: Qt.AlignVCenter
                                background: Rectangle { color: "lightblue"; border.color: "white" }
                                font.pixelSize: cellFontSize
                                text: sectorPid
                            }
                            Label {
                                Layout.preferredWidth: listView.width / 15 * 3
                                Layout.fillHeight: true
                                horizontalAlignment: Qt.AlignHCenter
                                verticalAlignment: Qt.AlignVCenter
                                background: Rectangle { color: "lightgray"; border.color: "white" }
                                font.pixelSize: cellFontSize
                                text: total
                            }
                            Label {
                                Layout.preferredWidth: listView.width / 15 * 3
                                Layout.fillHeight: true
                                horizontalAlignment: Qt.AlignHCenter
                                verticalAlignment: Qt.AlignVCenter
                                background: Rectangle { color: "lightgreen"; border.color: "white" }
                                font.pixelSize: cellFontSize
                                text: max
                            }
                            Label {
                                Layout.preferredWidth: listView.width / 15 * 3
                                Layout.fillHeight: true
                                horizontalAlignment: Qt.AlignHCenter
                                verticalAlignment: Qt.AlignVCenter
                                background: Rectangle { color: "yellow"; border.color: "white" }
                                font.pixelSize: cellFontSize
                                text: avg
                            }
                        }
                    }
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (central.state == 'inGrid') {
                        gridItem.GridView.view.currentIndex = index;
                        central.state = 'inBrowser';
                    } else {
                        central.state = 'inGrid';
                    }
                }
            }

            states: [
                State {
                    name: "inGrid"; when: central.state == 'inGrid'
                    ParentChange { target: delegateItem; parent: gridItem }
                    PropertyChanges { target: delegateItem; width: grid.cellWidth; height: grid.cellHeight }
                },
                State {
                    name: "inBrowser"; when: central.state == 'inBrowser'
                    ParentChange { target: delegateItem; parent: browserItem }
                    PropertyChanges { target: delegateItem; width: browser.width; height: browser.height; x: 0; y: 0 }
//                    PropertyChanges { target: delegateItem; width: height /2; height: browser.height; x: 0; y: 0 }
                }
            ]
//            transitions: [
//            Transition {
//                from: '*'; to: 'browser'
//                SequentialAnimation {
//                    NumberAnimation { target: delegateItem; properties: 'width, height, opacity'; duration: 250; easing.type: Easing.OutQuad }
////                    PauseAnimation { duration: 350 }
////                    NumberAnimation { target: backButton; properties: "y"; duration: 200; easing.type: Easing.OutQuad }
//                }
//            }
//            ]




        }
    }
}
