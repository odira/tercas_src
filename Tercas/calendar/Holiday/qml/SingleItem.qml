import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQml.Models 2.12

ColumnLayout {

    ScrollView {
        id: scrollSingle
        Layout.fillWidth: true
        Layout.fillHeight: true
        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

        ListView {
            id: singleView
            Layout.preferredWidth: 500
            Layout.fillHeight: true
            model: visualModel.parts.single
            snapMode: ListView.SnapOneItem
            orientation: ListView.Horizontal
            visible: true
            clip: true
            boundsBehavior: ListView.StopAtBounds

            highlightMoveDuration: 0
        }
    }

    SingleFooter {
        id: singleFooter
        Layout.fillWidth: true
        Layout.fillHeight: false
        Layout.preferredHeight: 60
    }

}
