import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    RowLayout {
        Layout.fillWidth: true
        Layout.fillHeight: true
        spacing: 5

        TextField {
            Layout.preferredWidth: 150
            Layout.fillHeight: true
            text: surname
            font.bold: true
            background: Rectangle {
                implicitHeight: 40
                border.color: 'pink'
            }
        }
        TextField {
            Layout.preferredWidth: 150
            Layout.fillHeight: true
            text: name
            background: Rectangle {
                border.color: 'pink'
            }
        }
        TextField {
            Layout.preferredWidth: 150
            Layout.fillHeight: true
            text: middlename
            background: Rectangle {
                border.color: 'pink'
            }
        }
        TextField {
            Layout.preferredWidth: 50
            Layout.fillHeight: true
            text: birthday.toLocaleDateString(Qt.locale("ru_RU"), "yyyy")
            background: Rectangle {
                border.color: 'pink'
            }
        }
        TextField {
            Layout.preferredWidth: 250
            Layout.fillHeight: true
            text: position
            background: Rectangle {
                border.color: 'pink'
            }
        }
        TextField {
            Layout.preferredWidth: 40
            Layout.fillHeight: true
            text: model.class
            horizontalAlignment: TextField.AlignHCenter
            background: Rectangle {
                border.color: 'pink'
            }
        }
        TextField {
            Layout.preferredWidth: 40
            Layout.fillHeight: true
            text: shift_num
            horizontalAlignment: TextField.AlignHCenter
            background: Rectangle {
                border.color: 'pink'
            }
        }
        TextField {
            Layout.preferredWidth: 250
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
            singleView.currentIndex = index
            view.state = 'inSingle'
        }
    }
}
