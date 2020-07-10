import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {

    property bool isCurIdx: ListView.isCurrentItem
    property color selectedColor: '#F5D788'
    property color nonselectedColor: '#F8EFD4'

    RowLayout {
        anchors.fill: parent

        TextField {
            Layout.preferredWidth: 50
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: date.toLocaleDateString(Qt.locale("ru_RU"), "dd MMMM yyyy")
            font.bold: isCurIdx ? true : false
//            font.pixelSize: isCurIdx ? 13 : 12
//            background: Rectangle {
//                border.color: 'pink'
//                color: isCurIdx ? selectedColor : nonselectedColor
//            }
        }
        TextField {
            Layout.preferredWidth: 150
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: type
        }
        TextField {
            Layout.preferredWidth: 200
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: note
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
        showSingle()
    }
}
