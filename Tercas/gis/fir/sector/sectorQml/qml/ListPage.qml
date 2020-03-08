import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page {
    id: root

    header: ToolBar {
        Label {
            anchors.centerIn: parent
            text: qsTr("База данных секторов РДЦ")
            font.pixelSize: 16
        }
    }

    ListView {
        id: listView

        anchors.fill: parent
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.topMargin: 5
        anchors.bottomMargin: 5
        spacing: 20
        model: sectorModel
        clip: true
        displayMarginBeginning: 40
        displayMarginEnd: 40
        delegate: ItemDelegate {
            width: ListView.view.width - ListView.view.leftMargin - ListView.view.rightMargin
            height: column.height
            clip: true

            ColumnLayout {
                id: column

                RowLayout {
                    id: fullname

                    Label {
                        font.pixelSize: 16
                        font.bold: true
                        text: model.fullname
                    }
                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        visible: model.compound
                        font.italic: true
                        font.pixelSize: 12
                        text: qsTr("(Совмещенный)")
                    }
                }
                RowLayout {
                    id: label

                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        font.italic: true
                        text: qsTr("Сокращенное наименование: ")
                    }
                    Label {
                        font.pixelSize: 12
                        font.bold: true
                        text: model.label
                    }
                }
            }

            onClicked: root.StackView.view.push("qrc:/qml/ItemPage.qml", { row: index })
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
