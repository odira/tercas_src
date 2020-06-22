import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Dialog {
    id: yesNoDialog
//    implicitWidth: menuDialog.width
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
//        holidayModel.deleteRow(currentRow)
//        holidayModel.submitDB()
//        menuDialog.close()
    }
//    onRejected: menuDialog.close()
}
