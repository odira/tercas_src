import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Package {

    Item {
        id: listDelegate
        Package.name: 'list'
        width: parent.width; height: 60

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true

            Rectangle {
//                Layout.fillHeight: true
                height: listDelegate.height
                Layout.preferredWidth: 200
                border.color: "red"

            ColumnLayout {
                id: nameBox
                Layout.fillHeight: true
//                Layout.preferredWidth: 200
                Layout.fillWidth: true
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
            }
//            ColumnLayout {
//                id: birthdayBox
//                Layout.fillHeight: true
//                Layout.preferredWidth: 130
//                spacing: 0

//                TextField {
//                    font.bold: true
//                    text: birthday.getFullYear()
//                    background: Rectangle { border.color: "transparent" }
//                }
//                TextField {
//                    text: birthday.toLocaleString(Qt.locale("ru_RU"), "dd MMMM")
//                    background: Rectangle { border.color: "transparent" }
//                }
//            }
//            ColumnLayout {
//                id: mobile_phoneBox
//                Layout.fillHeight: true
//                Layout.preferredWidth: 160
//                spacing: 0

//                TextField {
//                    text: mobile_phone
//                    background: Rectangle { border.color: "transparent" }
//                }
//            }

//            TextField { text: tab_num }

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
//                    background: Rectangle { border.color: "transparent" }
                }
            }

            ColumnLayout {
                id: classBox
                Layout.fillHeight: true
                Layout.preferredWidth: 150
                spacing: 0

                TextField {
                    Layout.fillHeight: true
                    horizontalAlignment: TextField.AlignHCenter
                    verticalAlignment: TextField.AlignVCenter
                    text: qsTr(model.class + " класс")
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
//            TextField { text: sectors_pool }
//            TextField { text: admission }
//            TextField { text: note }
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
