import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQml.Models 2.12

ApplicationWindow {
    id: root
    visible: true
    width: Screen.width
    height: Screen.height
    title: qsTr("Период активности")

    DelegateModel {
        id: visualModel
        model: periodModel
        delegate: Delegate {}
    }

    ListView {
        id: view
        anchors.fill: parent
        anchors.margins: 10
        model: visualModel
    }
}
