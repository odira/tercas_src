import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Dialog {
    id: searchDialog

    title: qsTr("Search Dialog")

    property var whatField
    property var whatText

    contentItem: ColumnLayout {
        ComboBox {
            id: combo
            textRole: "key"
            model: searchComboModel
            onActivated: {
                whatField = searchComboModel.get(index).value
                searchField.focus = true
            }
        }
        TextField {
            id: searchField
            placeholderText: qsTr("Введите текст для поиска...")
            font.pixelSize: 16

            onTextChanged: {
                whatText = text
                emplSectorCheckModel.applyFilter(whatField + " ILIKE " + "'" + whatText + "'");
            }
        }
    }
    footer: DialogButtonBox {
        Button {
            text: qsTr("Search")
        }
        Button {
            text: qsTr("Close")
            DialogButtonBox.buttonRole: DialogButtonBox.RejectRole
        }
    }

    ListModel {
        id: searchComboModel

        ListElement {
            key: "Работник"
            value: "personfullname"
        }
        ListElement {
            key: "Сектор"
            value: "sectorlabel"
        }
    }

    Behavior on visible {
        NumberAnimation { duration: 300 }
    }
}
