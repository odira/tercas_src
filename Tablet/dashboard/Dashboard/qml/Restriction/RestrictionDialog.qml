import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Dialog {
    id: dialog

    signal finished(string ad,
                    string indxMil,
                    string callSign,
                    string zone,
                    string levelFrom,
                    string levelTo,
                    string timeFrom,
                    string timeTo,
                    string note)

    function createRestriction() {
        grid.ad.editText = "";
        grid.indxMil.editText = "";
        grid.callSign.editText = "";
        grid.zone.clear();
        grid.levelFrom.editText = "";
        grid.levelTo.editText = "";
        grid.timeFrom.clear();
        grid.timeTo.clear();
        grid.note.clear();

        dialog.title = qsTr("Добавить ограничение");
        dialog.open();
    }

    function editRestriction(restriction) {
        grid.ad.editText = restriction.ad;
        grid.indxMil.editText = restriction.indxMil;
        grid.callSign.editText = restriction.callSign;
        grid.zone.text = restriction.zone;
        grid.levelFrom.editText = restriction.levelFrom;
        grid.levelTo.editText = restriction.levelTo;
        grid.timeFrom.text = restriction.timeFrom;
        grid.timeTo.text = restriction.timeTo;
        grid.note.text = restriction.note;

        dialog.title = qsTr("Редактировать ограничение");
        dialog.open();
    }

    width: parent.width * 6 / 7
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2
    focus: true
    modal: true
    font.pixelSize: 18

    standardButtons: Dialog.Ok | Dialog.Cancel
    onAccepted: finished(grid.ad.editText,
                         grid.indxMil.editText,
                         grid.callSign.editText,
                         grid.zone.text,
                         grid.levelFrom.editText,
                         grid.levelTo.editText,
                         grid.timeFrom.text,
                         grid.timeTo.text,
                         grid.note.text);

    contentItem: GridLayout {
        id: grid

        property alias ad: ad
        property alias indxMil: indxMil
        property alias callSign: callSign
        property alias zone: zone
        property alias levelFrom: levelFrom
        property alias levelTo: levelTo
        property alias timeFrom: timeFrom
        property alias timeTo: timeTo
        property alias note: note
        property int minimumInputSize: 120

        rows: 9
        columns: 1

        // Наименование
        Label {
            text: qsTr("Наименование точки")
            Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
        }
        RowLayout {
            ComboBox {
                id: ad
                Layout.fillWidth: true
                editable: true
                model: ListModel {
                    id: adModel
                    ListElement { text: "Липецк-2" }
                    ListElement { text: "Мичуринск" }
                    ListElement { text: "Раменское" }
                }
            }
            ComboBox {
                id: indxMil
                editable: true
            }
        }

        // Позывной точки
        Label {
            text: qsTr("Позывной точки")
            Layout.alignment: Qt.AlignLeft
        }
        ComboBox {
            id: callSign
            Layout.fillWidth: true
            editable: true
            model: ListModel {
                id: callSignModel
                ListElement { text: "Ворсовка" }
                ListElement { text: "Сатурн" }
                ListElement { text: "Гордый" }
            }
        }

        Label {
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            text: qsTr("Номер зоны")
        }
        TextField {
            id: zone
            Layout.fillWidth: true
            Layout.minimumWidth: grid.minimumInputSize
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            placeholderText: qsTr("<Введите номер зоны>")
        }

        Label {
            text: qsTr("Эшелоны работы")
            Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
        }
        RowLayout {
            ComboBox {
                id: levelFrom
                Layout.fillWidth: true
                editable: true
                model: levelModel
            }
            ComboBox {
                id: levelTo
                Layout.fillWidth: true
                editable: true
                model: levelModel
            }
        }

        Label {
            text: qsTr("Время работы")
            Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
        }
        RowLayout {
            TextField {
                id: timeFrom
                Layout.fillWidth: true
                Layout.minimumWidth: grid.minimumInputSize
                Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
                placeholderText: qsTr("<С>")
            }
            TextField {
                id: timeTo
                Layout.fillWidth: true
                Layout.minimumWidth: grid.minimumInputSize
                Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
                placeholderText: qsTr("<По>")
            }
        }
        Label {
            text: qsTr("Примечание")
            Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
        }
        TextField {
            id: note
            Layout.fillWidth: true
            Layout.minimumWidth: grid.minimumInputSize
            Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
            placeholderText: qsTr("<Введите примечание>")
        }
    }

    Component.onCompleted: ad.focus = true

    ListModel {
        id: levelModel
        ListElement { text: "GND" }
        ListElement { text: "FL40" }
        ListElement { text: "FL50" }
        ListElement { text: "FL60" }
        ListElement { text: "FL70" }
        ListElement { text: "FL80" }
        ListElement { text: "FL90" }
        ListElement { text: "FL100" }
        ListElement { text: "FL110" }
        ListElement { text: "FL120" }
        ListElement { text: "FL130" }
        ListElement { text: "FL140" }
        ListElement { text: "FL150" }
        ListElement { text: "FL160" }
        ListElement { text: "FL170" }
        ListElement { text: "FL180" }
        ListElement { text: "FL190" }
        ListElement { text: "FL200" }
        ListElement { text: "FL210" }
        ListElement { text: "FL220" }
        ListElement { text: "FL230" }
        ListElement { text: "FL240" }
        ListElement { text: "FL250" }
        ListElement { text: "FL260" }
        ListElement { text: "FL270" }
        ListElement { text: "FL280" }
        ListElement { text: "FL290" }
        ListElement { text: "FL300" }
        ListElement { text: "FL310" }
        ListElement { text: "FL320" }
        ListElement { text: "FL330" }
        ListElement { text: "FL340" }
        ListElement { text: "FL350" }
        ListElement { text: "FL360" }
        ListElement { text: "FL370" }
        ListElement { text: "FL380" }
        ListElement { text: "FL390" }
        ListElement { text: "FL400" }
        ListElement { text: "FL410" }
        ListElement { text: "FL430" }
        ListElement { text: "FL450" }
        ListElement { text: "FL470" }
        ListElement { text: "FL490" }
        ListElement { text: "FL510" }
        ListElement { text: "FL530" }
        ListElement { text: "UNL" }
    }
}
