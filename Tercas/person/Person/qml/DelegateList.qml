import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    RowLayout {
//        Layout.fillWidth: true
//        Layout.fillHeight: true
        anchors.fill: parent

        TextField {
            Layout.preferredWidth: 200
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: surname
            font.bold: true
            background: Rectangle {
                border.color: 'pink'
            }
        }
        TextField {
            Layout.preferredWidth: 150
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: model.name
            background: Rectangle {
                border.color: 'pink'
            }
        }
        TextField {
            Layout.preferredWidth: 150
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: middlename
            background: Rectangle {
                border.color: 'pink'
            }
        }
        TextField {
            Layout.preferredWidth: 50
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: birthday.toLocaleDateString(Qt.locale("ru_RU"), "yyyy")
            horizontalAlignment: TextField.AlignHCenter
            background: Rectangle {
                border.color: 'pink'
            }
        }
        TextField {
            Layout.preferredWidth: 200
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: position
            background: Rectangle {
                border.color: 'pink'
            }
        }
        TextField {
            Layout.preferredWidth: 45
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: model.class
            horizontalAlignment: TextField.AlignHCenter
            background: Rectangle {
                border.color: 'pink'
            }
        }
        TextField {
            Layout.preferredWidth: 45
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: shift_num
            horizontalAlignment: TextField.AlignHCenter
            background: Rectangle {
                border.color: 'pink'
            }
        }
        TextField {
            Layout.preferredWidth: 200
            Layout.fillWidth: true
            Layout.fillHeight: true
            text: sectors_pool
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
}
