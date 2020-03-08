import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page {
    id: root

    property int row

    header: ToolBar {
        ToolButton {
            contentItem: Rectangle {
                width: 20
                height: 20
                anchors.left: parent.left
                anchors.leftMargin: 20
                color: "transparent"
                Image {
                    anchors.fill: parent
                    rotation: 180
                    source: "qrc:arrow"
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: root.StackView.view.pop()
                }
            }
        }
        Label {
            anchors.centerIn: parent
            font.pixelSize: 16
            text: qsTr("Данные по сектору ") + sectorModel.get(row).label
        }
    }

    ColumnLayout {
        id: column

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 20
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        spacing: 10

        RowLayout {
            id: fullname

            Label {
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 12
                text: qsTr("Полное наименование: ")
            }
            Label {
                font.pixelSize: 16
                font.bold: true
                text: sectorModel.get(row).fullname
            }
        }
        RowLayout {
            id: label

            Label {
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 12
                text: qsTr("Сокращенное наименование: ")
            }
            Label {
                font.pixelSize: 16
                font.bold: true
                text: sectorModel.get(row).label
            }
        }
        CheckBox {
            id: compound

            text: qsTr(" Совмещенный")
            checked: sectorModel.get(row).compound === 'true' ? true : false
        }
        RowLayout {
            id: freq

            visible: sectorModel.get(row).freq != 0 ? true : false

            Label {
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 12
                font.italic: true
                text: qsTr("Частота: ")
            }
            Label {
                font.pixelSize: 16
                font.bold: true
                text: sectorModel.get(row).freq + qsTr("МГц")
            }
        }
        Frame {
            id: phone

            visible: (sectorModel.get(row).terkasphone != 0 || sectorModel.get(row).cupphone != 0) ? true : false

            ColumnLayout {
                spacing: 10

                RowLayout {
                    id: tercasphone

                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 12
                        font.italic: true
                        text: qsTr("Телефон TERCAS: ")
                    }
                    Label {
                        font.pixelSize: 16
                        font.bold: true
                        text: sectorModel.get(row).terkasphone
                    }
                }
                RowLayout {
                    id: cupphone

                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 12
                        font.italic: true
                        text: qsTr("Телефон ЦУП: ")
                    }
                    Label {
                        font.pixelSize: 16
                        font.bold: true
                        text: sectorModel.get(row).cupphone
                    }
                }
            }
        }
        Frame {
            id: nps

            visible: (sectorModel.get(row).npsdz != 0 || sectorModel.get(row).npspdz != 0) ? true : false

            ColumnLayout {
                spacing: 10

                RowLayout {
                    id: npsdz

                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 12
                        font.italic: true
                        text: qsTr("Допустимая загрузка: ")
                    }
                    Label {
                        font.pixelSize: 16
                        font.bold: true
                        text: sectorModel.get(row).npsdz + qsTr(" ВС/час")
                    }
                }
                RowLayout {
                    id: npspdz

                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 12
                        font.italic: true
                        text: qsTr("Предельно-допустимая загрузка: ")
                    }
                    Label {
                        font.pixelSize: 16
                        font.bold: true
                        text: sectorModel.get(row).npspdz + qsTr(" ВС/час")
                    }
                }
            }
        }
    }

    footer: ToolBar {
        Label {
            anchors.centerIn: parent
            font.pixelSize: 16
            text: qsTr("Footer")
        }
    }
}
