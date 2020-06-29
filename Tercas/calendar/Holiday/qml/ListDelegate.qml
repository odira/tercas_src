import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
//    id: listDelegate

    property bool isCurIdx: ListView.isCurrentItem

    RowLayout {
        anchors.fill: parent
        anchors.topMargin: 5
        anchors.bottomMargin: 5

        TextField {
            Layout.preferredWidth: 50
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: date.toLocaleDateString(Qt.locale("ru_RU"), "dd MMMM yyyy")
            font.bold: isCurIdx ? true : false
            font.pixelSize: isCurIdx ? 13 : 12
            background: Rectangle {
                border.color: 'pink'
                color: isCurIdx ? '#FFB900' : 'transparent'
            }
        }
        TextField {
            Layout.preferredWidth: 150
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: type
            font.bold: isCurIdx ? true : false
            font.pixelSize: isCurIdx ? 13 : 12
            background: Rectangle {
                border.color: 'pink'
                color: isCurIdx ? '#FFB900' : 'transparent'
            }
        }
        TextField {
            Layout.preferredWidth: 200
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: note
            font.bold: isCurIdx ? true : false
            font.pixelSize: isCurIdx ? 13 : 12
            background: Rectangle {
                border.color: 'pink'
                color: isCurIdx ? '#FFB900' : 'transparent'
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            listView.currentIndex = index
            showSingle()
        }
    }

    Keys.onReturnPressed: {
        listView.currentIndex = index
        showSingle()
    }
}
