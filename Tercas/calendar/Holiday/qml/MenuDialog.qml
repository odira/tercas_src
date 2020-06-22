import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

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
            onClicked: showHoliday()
        }
        RoundButton {
            Layout.fillWidth: true
            radius: 2
            text: qsTr("Add New Row")
            onClicked: addHoliday()
        }
        RoundButton {
            Layout.fillWidth: true
            radius: 2
            text: qsTr("Delete Current Row")
            onClicked: deleteHoliday()
        }
    }
}


//Dialog {
//    id: menuDialog
//    width: parent.width / 4
////    height: 60
//    anchors.centerIn: parent
//    modal: true
//    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

//    property int currentRow: 0

//    contentItem: ColumnLayout {
//        RoundButton {
//            Layout.fillWidth: true
//            radius: 2
//            text: qsTr("Show Item")
//            onClicked: {
//                holidayDialog.currentRow = currentRow
//                holidayDialog.open()
//            }
//        }
//        RoundButton {
//            Layout.fillWidth: true
//            radius: 2
//            text: qsTr("Delete Current Row")
//            onClicked: {
//                yesNoDialog.open()
//            }
//        }
//    }

//    Dialog {
//        id: yesNoDialog
//        implicitWidth: menuDialog.width
//        anchors.centerIn: parent
//        modal: true
//        standardButtons: Dialog.Yes | Dialog.No

//        contentItem: ColumnLayout {
//            TextField {
//                Layout.fillWidth: true
//                text: qsTr("Are you sure?")
//            }
//        }
//        onAccepted: {
//            holidayModel.deleteRow(currentRow)
//            holidayModel.submitDB()
//            menuDialog.close()
//        }
//        onRejected: menuDialog.close()
//    }

//    HolidayDialog {
//        id: holidayDialog
//    }
//}
