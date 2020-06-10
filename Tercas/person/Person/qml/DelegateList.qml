import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    RowLayout {
        Layout.fillWidth: true
        Layout.fillHeight: true
        spacing: 5

        Rectangle {
            Layout.fillHeight: true
            Layout.preferredWidth: 200
            border.color: "transparent"

            Column {
                id: nameBox
                anchors.fill: parent
                anchors.margins: 1
                spacing: 0

                Text {
                    font.bold: true
                    font.pixelSize: 16
                    color: "brown"
                    text: surname
                }
                Text {
                    font.pixelSize: 12
                    text: name + " " + middlename
                }
            }
        }
        ColumnLayout {
            id: positionBox
            Layout.fillHeight: true
            Layout.preferredWidth: 200
            spacing: 0

            TextField {
                Layout.fillHeight: true
                horizontalAlignment: TextField.AlignHCenter
                verticalAlignment: TextField.AlignVCenter
                text: position
            }
        }
        ColumnLayout {
            id: classBox
            Layout.fillHeight: true
            Layout.preferredWidth: 200
            spacing: 0

            TextField {
                Layout.fillHeight: true
                horizontalAlignment: TextField.AlignHCenter
                verticalAlignment: TextField.AlignVCenter
                text: {
                    var text = model.class + " класс"
                    return text
                }
            }
        }
        ColumnLayout {
            id: shift_numBox
            Layout.fillHeight: true
            Layout.preferredWidth: 150
            spacing: 0

            TextField {
                Layout.fillHeight: true
                horizontalAlignment: TextField.AlignHCenter
                verticalAlignment: TextField.AlignVCenter
                text: qsTr("Смена № " + shift_num)
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
