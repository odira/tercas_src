import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    RowLayout {
        anchors.fill: parent

        TextField {
            Layout.preferredWidth: 50
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: date.toLocaleDateString(Qt.locale("ru_RU"), "dd MMMM yyyy")
            font.bold: true
            background: Rectangle {
                border.color: 'pink'
            }
        }
        TextField {
            Layout.preferredWidth: 150
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: type
            background: Rectangle {
                border.color: 'pink'
            }
        }
        TextField {
            Layout.preferredWidth: 200
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: note
            background: Rectangle {
                border.color: 'pink'
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


            focus: true
            Keys.onDownPressed: {
                currentIndex = currentIndex + 1
            }
            Keys.onPressed: {
                console.log(currentIndex)
            }


}
