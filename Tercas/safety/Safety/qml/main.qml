import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQml.Models 2.12

import Wiipuri.Models 1.0

ApplicationWindow {
    id: rootWindow
    width: Screen.width
    height: Screen.height
    visible: true
    title: qsTr("Безопасность полетов")

    SafetyModel { id: safetyModel }
    DelegateModel { id: storeVisualModel; model: safetyModel; delegate: StoreDelegate {} }

    ListView {
        id: fullscreenView

        enabled: false
        opacity: 0.0

        anchors.fill: parent
        anchors.margins: 10
        clip: true
        snapMode: ListView.SnapOneItem
        orientation: ListView.Horizontal
        model: storeVisualModel.parts.fullscreen
        highlightMoveDuration: 100
        onCurrentIndexChanged: {
            listView.currentIndex = index
        }
    }

    ListView {
        id: listView

        enabled: true
        opacity: 1.0
        focus: true

        anchors.fill: parent
        anchors.margins: 10
        clip: true
        snapMode: ListView.SnapToItem
        spacing: 10
        model: storeVisualModel.parts.list

        highlight: Rectangle { color: "red" }
        highlightFollowsCurrentItem: true

//        onCurrentIndexChanged: fullscreenView.currentIndex = currentIndex
    }
    

//    Rectangle {
//        id: listRoot
//        anchors.fill: parent
//        anchors.margins: 20

//        ListView {
//            id: list
//            anchors.fill: parent
//            model: safetyModel
//            orientation: ListView.Horizontal
//            snapMode: ListView.SnapToItem
//            clip: true
//            delegate: Rectangle {
//                width: list.width
//                height: list.height
//                color: 'lightblue'
//                Text {
//                    anchors.centerIn: parent
//                    text: model._1
//                }
//            }
//        }
//    }

//    Rectangle {
//        id: path
//        anchors.fill: parent
//        anchors.margins: 100
//        z: 2

//        PathView {
//            anchors.fill: parent
//            model: safetyModel
//            delegate: Rectangle {
//                width: 300
//                height: 300
//                color: "blue"
//                Text {
//                    anchors.centerIn: parent
//                    text: model._1
//                }
//            }
//            path: Path {
//                startX: path.width; startY: path.height
////                startX: rootWindow.width/2; startY: rootWindow.height/2
////                PathLine { x: rootWindow.width/2; y: rootWindow.height/2 }
//            }
//        }
//    }

//    Rectangle {
//        id: table
//        anchors.fill: parent
//        anchors.margins: 20
//        border.color: "grey"
//        enabled: false
//        visible: false
//        z: 1

//        TableView {
//            id: tableView

//            property var columnWidths: [
//                0,                          // SafetyModel_pid
//                tableView.width / 100 * 20, // SafetyModel_ts
//                0,                          // SafetyModel_accpid
//                tableView.width / 100 * 15, // SafetyModel_acc
//                0,                          // SafetyModel_departmentpid
//                tableView.width / 100 * 15, // SafetyModel_department
//                tableView.width / 100 * 5,  // SafetyModel_shift
//                0,                          // SafetyModel_sectorpid
//                0,                          // SafetyModel_sector
//                tableView.width / 100 * 14, // SafetyModel_sectorlabel
//                0,                          // SafetyModel_sectorcolor
//                tableView.width / 10,       // SafetyModel_node_pid
//                0,                          // SafetyModel_classificationpid
//                0,                          // SafetyModel_classification
//                tableView.width / 100 * 5,  // SafetyModel_classificationabbr
//                0,                          // SafetyModel_typepid
//                0,                          // SafetyModel_type
//                0,                          // SafetyModel_cause
//                0,                          // SafetyModel_factor
//                0,                          // SafetyModel_details
//                0,                          // SafetyModel_note
//                0,                          // SafetyModel_spospid
//                tableView.width / 100 * 5,  // SafetyModel_spos
//                0,                          // SafetyModel_tcas1pid
//                tableView.width / 100 * 5,  // SafetyModel_tcas1
//                0,                          // SafetyModel_tcas2pid
//                tableView.width / 100 * 5   // SafetyModel_tcas2
//            ]
//            columnWidthProvider: function (column) { return columnWidths[column] }

//            anchors.fill: parent
//            anchors.margins: 1
//            model: safetyModel
//            clip: true

//            columnSpacing: 2
//            rowSpacing: 2
//            delegate: Rectangle {
//                implicitHeight: 50
//                border.color: "grey"
//                Text {
//                    anchors.fill: parent
//                    anchors.leftMargin: { if (column === 3 || column === 5 || column === 6 || column === 14) return 0; return 10; }
//                    horizontalAlignment: {
//                        if (column === 3 || column === 5 || column === 6 || column === 14)
//                            return Text.AlignHCenter;
//                        return Text.AlignLeft
//                    }
//                    verticalAlignment: Text.AlignVCenter
//                    wrapMode: { if (column === 3 || column === 5) return Text.WordWrap; return Text.WrapAnywhere; }
//                    text: model.display
//                }
//                MouseArea {
//                    anchors.fill: parent
//                    onClicked: console.log(model._0)
//                }
//            }
//        }
//    }

    footer: Row {
        id: footer
        width: parent.width
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottomMargin: 10
        height: 80
        layoutDirection: Qt.RightToLeft
        spacing: 10

        Button {
            text: qsTr("Close")
            onClicked: Qt.quit()
        }
        Button {
            text: qsTr("Plot")
//            onClicked: {
//                var year = sectorMonthModel.getModelYear()
//                var appPath = '/Users/tercas/Programming/src/Tercas/statistics/sector/month/SectorMonth/py/plotSectorMonth.py ' + year
//                process.start(appPath)
//            }
        }
    }
}
