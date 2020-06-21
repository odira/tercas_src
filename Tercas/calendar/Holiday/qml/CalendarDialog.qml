import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls 1.4

Dialog {
    id: calendarDialog
    title: qsTr("Выберите дату")
    anchors.centerIn: parent
    modal: true
    standardButtons: Dialog.Ok | Dialog.Close

    property date calendarDate: new Date()

    Calendar {
        id: calendarButton
        anchors.fill: parent
        selectedDate: calendarDate
        onClicked: calendarDate = date
    }
}
