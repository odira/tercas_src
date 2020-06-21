import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.4

ApplicationWindow {
    id: root
    visible: true
    width: 1200
    height: 800
    title: qsTr("Производственный календарь праздничных, выходных и рабочих дней")

    header: Rectangle {
        height: 40
        color: "orange"
    }

    contentData: TableView {
        id: view
        anchors.fill: parent
//        anchors.topMargin: 2
        anchors.margins: 5
        model: holidayModel
        columnSpacing: 2
        rowSpacing: 5
        clip: true
        reuseItems: false

        property var columnWidths: [1, 100, 300, view.width - 100 - 300 - 1 - 1 - 1 - 1 - 1 - 1]

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
                    menuDialog.currentRow = row
                    menuDialog.open()
                }
            }
        }
    }

    footer: Rectangle {
        height: 40
        color: "orange"
    }

    Dialog {
        id: menuDialog
        width: parent.width / 4
        anchors.centerIn: parent
        modal: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        property int currentRow: 0

        contentItem: ColumnLayout {
            RoundButton {
                Layout.fillWidth: true
                radius: 2
                text: qsTr("Show Item")
                onClicked: {
                    holidayDialog.currentRow = menuDialog.currentRow
                    holidayDialog.currentState = "NORMAL"
                    holidayDialog.open()
                    menuDialog.close()
                }
            }
            RoundButton {
                Layout.fillWidth: true
                radius: 2
                text: qsTr("Add New Row")
                onClicked: {
                    holidayDialog.currentRow = menuDialog.currentRow
                    holidayDialog.currentState = "ADD"
                    holidayDialog.open()
                    menuDialog.close()
                }
            }
            RoundButton {
                Layout.fillWidth: true
                radius: 2
                text: qsTr("Delete Current Row")
                onClicked: {
                    yesNoDialog.open()
                    yesNoDialog.currentRow = menuDialog.currentRow
                    menuDialog.close()
                }
            }
        }
    }

    Dialog {
        id: yesNoDialog
        implicitWidth: menuDialog.width
        anchors.centerIn: parent
        modal: true
        standardButtons: Dialog.Yes | Dialog.No

        property int currentRow: 0

        contentItem: ColumnLayout {
            TextField {
                Layout.fillWidth: true
                text: qsTr("Are you sure?")
            }
        }
        onAccepted: {
            holidayModel.deleteRow(currentRow)
            holidayModel.submitDB()
            menuDialog.close()
        }
        onRejected: menuDialog.close()
    }

    HolidayDialog {
        id: holidayDialog
    }
}
