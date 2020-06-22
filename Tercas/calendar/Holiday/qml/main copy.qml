import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.4

ApplicationWindow {
    id: root
    visible: true
    width: 1200
    height: 800
    title: qsTr("Производственный календарь праздничных, выходных и рабочих дней")

//    menuBar: Item {

//    }

    function showHoliday() {
//        holidayDialog.currentRow = menuDialog.currentRow
        holidayDialog.currentRow = view.currentRow
        holidayDialog.currentState = "NORMAL"
        holidayDialog.open()
//        menuDialog.close()
    }
    function addHoliday() {
        //        holidayDialog.currentRow = menuDialog.currentRow
        holidayDialog.currentRow = view.currentRow
        holidayDialog.currentState = "ADD"
        holidayDialog.open()
//        menuDialog.close()
    }
    function deleteHoliday() {
        yesNoDialog.open()
//        yesNoDialog.currentRow = menuDialog.currentRow
        holidayDialog.currentRow = view.currentRow
//        menuDialog.close()
    }

    header: Item {
        height: 70

        RowLayout {
            anchors.fill: parent
            anchors.margins: 10

            RoundButton {
                Layout.fillHeight: true
                Layout.preferredWidth: 100
                radius: 0
                text: qsTr("Show")
                onClicked: showHoliday()
            }
            RoundButton {
                Layout.fillHeight: true
                Layout.preferredWidth: 100
                radius: 0
                text: qsTr("Add")
                onClicked: addHoliday()
            }
            RoundButton {
                Layout.fillHeight: true
                Layout.preferredWidth: 100
                radius: 0
                text: qsTr("Delete")
                onClicked: deleteHoliday()
            }
            Item {
                id: spacing
                Layout.fillWidth: true
            }
            RoundButton {
                Layout.fillHeight: true
                Layout.preferredWidth: 100
                radius: 0
                text: qsTr("Quit")
                onClicked: Qt.quit()
            }
        }
    }

    contentData: TableView {
        id: view
        anchors.fill: parent
        anchors.margins: 5
        model: holidayModel
        columnSpacing: 2
        rowSpacing: 5
        clip: true
        reuseItems: false

        property int currentRow: 0
        property var columnWidths: [1, 100, 0, 300, view.width - 100 - 300 - 1 - 1 - 1 - 1 - 1 - 1]

        columnWidthProvider: function (column) { return columnWidths[column] }
        rowHeightProvider: function (row) { return 50 }

        delegate: Rectangle {
            TextField {
                id: text
                anchors.fill: parent
                clip: true
                text: display
                hoverEnabled: true
                horizontalAlignment: TextInput.AlignLeft
                wrapMode: TextInput.WordWrap
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
//                    menuDialog.currentRow = row
//                    menuDialog.open()
                    view.currentRow = row
                }
            }
        }
    }

    footer: Rectangle {
        height: 40
        color: "orange"
    }

//    MenuDialog { id: menuDialog }
    YesNoDialog { id: yesNoDialog }
    HolidayDialog { id: holidayDialog }
}
