import QtQuick 2.9

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
