import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2 as Dialogs

Page {
    id: root

    header: ToolBar {
        Label {
            anchors.centerIn: parent
            text: qsTr("Проверки на секторах РДЦ")
            font.pixelSize: 16
            font.bold: true
        }
    }

    ListView {
        id: listView
        anchors.fill: parent
        spacing: 20
        model: emplSectorCheckModel
        delegate: ItemDelegate {
            width: ListView.view.width - ListView.view.leftMargin - ListView.view.rightMargin
            height: column.implicitHeight

            ColumnLayout {
                id: column
                width: parent.width - 20
                anchors.horizontalCenter: parent.horizontalCenter


                Label {
                    id: personfullname
                    font.bold: true
                    font.pixelSize: 16
                    text: model.personfullname
                }
                Row {
                    spacing: 10

                    Label {
                        id: sectorlabel
                        text: model.sectorlabel
                        color: model.sectorcolor ? model.sectorcolor : "green"
                    }
                    Label {
                        id: sectorcheck
                        text: model.sectorcheck
                        font.pixelSize: 14
                    }
                    Label {
                        id: date
                        color: "blue"
                        text: Qt.formatDate(model.date, "dd MMMM yyyy")
                    }
                }
            }

            onClicked: root.StackView.view.push("qrc:/qml/ItemPage.qml", { row: index })
        }

        ScrollBar.vertical: ScrollBar {
            width: 20;
            visible: true
            policy: ScrollBar.AlwaysOn
        }
    }

    footer: ToolBar {
        Label {
            anchors.centerIn: parent
            font.pixelSize: 16
            text: qsTr("Footer")
        }
        ToolButton {
            text: "RELOAD"
            onClicked: emplSectorCheckModel.reload()
        }
        ToolBar {
            width: 50; height: parent.height
            anchors.right: parent.right
            anchors.rightMargin: 20

            contentItem: Rectangle {
                color: "transparent"

                Image {
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    source: "qrc:searchImage"
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: searchDialog.visible = true
                }
            }
        }
    }

   SearchDialog {
       id: searchDialog
       parent: root
       modal: true
       x: (parent.width - width) /2
       y: (parent.height - height) /2
   }
}
