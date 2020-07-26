import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: listDelegate
    width: ListView.view.width; height: layout.height + 5

    property bool isCurIdx: ListView.isCurrentItem

    RowLayout {
        id: layout
        width: parent.width; Layout.preferredHeight: children[0].height

        TextField {
            id: dateField
            Layout.preferredWidth: parent.width * 1/8
            text: date.toLocaleDateString(Qt.locale("ru_RU"), "dd MMMM yyyy")
            font.bold: isCurIdx ? true : false
            autoScroll: false
        }
        TextField {
            id: typeField
            Layout.preferredWidth: parent.width * 3/8
            text: type
            font.bold: isCurIdx ? true : false
            autoScroll: false
        }
        TextField {
            id: noteField
            Layout.fillWidth: true
            text: note
            font.bold: isCurIdx ? true : false
            wrapMode: TextInput.NoWrap
            autoScroll: false
//            hoverEnabled: true
//            ToolTip.visible: hovered
//            ToolTip.text: noteField.text
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            singleView.currentIndex = index
            showSingle()
        }
    }

    Keys.onReturnPressed: {
        singleView.currentIndex = listView.currentIndex
        showSingle()
    }
}
