import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Dialog {
    id: dialog

//    signal finished(string fullName, string sector, string seat, string startTime, string note)
    signal finished(string fullName, string sector, string seat)

    function createWatcher() {
//        grid.fullName.clear();
//        grid.sector.clear();
//        grid.seat.clear();
//        grid.startTime.clear();
//        grid.note.clear();

        dialog.title = qsTr("Добавить таймер");
        dialog.open();
    }

//    function edit(watcher) {
//        grid.fullName.text = watcher.fullName;
//        grid.sector.text = watcher.sector;
//        grid.seat.text = watcher.seat;
//        grid.startTime.text = watcher.startTime;
//        grid.note.text = watcher.note;

//        dialog.title = qsTr("Редактировать таймер");
//        dialog.open();
//    }

    width: parent.width * 4 / 5
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    focus: true
    modal: true
    font.bold: true
    font.pixelSize: 20

    standardButtons: Dialog.Ok | Dialog.Cancel
    onAccepted: // finished(grid.fullName.currentText, grid.sector.currentText, grid.seat.currentText, grid.startTime.text, grid.note.text);
    {
//        console.log(grid.fullName.currentText)
//        console.log(grid.sector.currentText)
//        console.log(grid.seat.currentText)
//        console.log(new Date())
        finished(grid.fullName.currentText, grid.sector.currentText, grid.seat.currentText);
    }

    contentItem: GridLayout {
        id: grid

        property alias fullName: fullName
        property alias sector: sector
        property alias seat: seat
//        property alias startTime: startTime
//        property alias note: note
        property int minimumInputSize: 120
        property string placeholderText: qsTr("<Введите текст>")

        rows: 3
        columns: 2

        Label {
            text: qsTr("Работник")
            Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
        }
//        TextField {
//            id: fullName
//            focus: true
//            Layout.fillWidth: true
//            Layout.minimumWidth: grid.minimumInputSize
//            Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
//            placeholderText: grid.placeholderText
//        }
        ComboBox {
            id: fullName
            Layout.fillWidth: true
            Layout.minimumWidth: grid.minimumInputSize
            Layout.alignment: Qt.AlignLeft
            model: [ "Ильин", "Береза", "Зыбина", "Лисяк", "Маркелов", "Платонова", "Степанов", "Степанова" ]
        }

        Label {
            text: qsTr("Сектор")
            Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
        }
//        TextField {
//            id: sector
//            Layout.fillWidth: true
//            Layout.minimumWidth: grid.minimumInputSize
//            Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
//            placeholderText: grid.placeholderText
//        }
        ComboBox {
            id: sector
            Layout.fillWidth: true
            Layout.minimumWidth: grid.minimumInputSize
            Layout.alignment: Qt.AlignHCenter
            model: [ "В1П1П2", "В1П2", "П1" ]
        }

        Label {
            text: qsTr("Место")
            Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
        }
//        TextField {
//            id: seat
//            Layout.fillWidth: true
//            Layout.minimumWidth: grid.minimumInputSize
//            Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
//            placeholderText: grid.placeholderText
//        }
        ComboBox {
            id: seat
            Layout.fillWidth: true
            Layout.minimumWidth: grid.minimumInputSize
            Layout.alignment: Qt.AlignHCenter
            model: [ "РЛУ", "ПК" ]
        }

//        Label {
//            text: qsTr("Начало отчета")
//            Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
//        }
//        TextField {
//            id: startTime
//            Layout.fillWidth: true
//            Layout.minimumWidth: grid.minimumInputSize
//            Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
//            placeholderText: grid.placeholderText
//        }

//        Label {
//            text: qsTr("Примечание")
//            Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
//        }
//        TextField {
//            id: note
//            Layout.fillWidth: true
//            Layout.minimumWidth: grid.minimumInputSize
//            Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
//            placeholderText: grid.placeholderText
//        }
    }
}
