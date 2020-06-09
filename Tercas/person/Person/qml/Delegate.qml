import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Package {

    Item {
        id: listDelegate
        Package.name: 'list'
        width: parent.width; height: 90

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true

            ColumnLayout {
                id: nameBox
                Layout.fillHeight: true
                Layout.preferredWidth: 200
                spacing: 0

                TextField {
                    font.bold: true
                    font.pixelSize: 20
                    text: surname
                    background: Rectangle { border.color: "transparent" }
                }
                TextField {
                    font.pixelSize: 16
                    text: name + " " + middlename
                    background: Rectangle { border.color: "transparent" }
                }
            }

            ColumnLayout {
                id: birthdayBox
                Layout.fillHeight: true
                Layout.preferredWidth: 130
                spacing: 0

                TextField {
                    font.bold: true
                    text: birthday.getFullYear()
                    background: Rectangle { border.color: "transparent" }
                }
                TextField {
                    text: birthday.toLocaleString(Qt.locale("ru_RU"), "dd MMMM")
                    background: Rectangle { border.color: "transparent" }
                }
            }

            TextField { text: mobile_phone }
            TextField { text: tab_num }
            TextField { text: position }
            TextField { text: 'class' }
            TextField { text: shift_num }
            TextField { text: sectors_pool }
            TextField { text: admission }
            TextField { text: note }
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                singleView.currentIndex = index
                view.state = 'inSingle'
            }
        }
    }

    Item {
        id: singleDelegate
        Package.name: 'single'
        width: root.width; height: root.height

        TextField {
            text: surname
        }
    }
}
