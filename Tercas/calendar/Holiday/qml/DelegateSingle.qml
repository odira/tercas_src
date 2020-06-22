import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: root

    function editItem() {

    }
    function saveItem() {

    }
    function discardItem() {

    }

    ColumnLayout {
        id: rootLayout
        anchors.fill: parent

        ColumnLayout {
            id: widgetBox
            Layout.fillWidth: true
            Layout.fillHeight: true
            enabled: false

            TextField {
                id: dateField
                Layout.fillWidth: true
                text: date.toLocaleDateString(Qt.locale("ru_RU"), "dd MMMM yyyy")
            }
            TextField {
                id: typeField
                Layout.fillWidth: true
                text: type
            }
            TextField {
                id: noteField
                Layout.fillWidth: true
                text: note
            }
            Item {
                id: spacing
                Layout.fillHeight: true
            }
        }

        Rectangle {
            id: bottonBox
            Layout.fillWidth: true
            height: 70
            border.color: 'pink'

            RowLayout {
                anchors.centerIn: parent
                height: parent.height - 10
                anchors.margins: 5

                RoundButton {
                    id: editButton
                    Layout.fillHeight: true
                    Layout.preferredWidth: 150
                    radius: 0
                    text: qsTr('Edit')

                    onClicked: editItem()

                    background: Rectangle {
                        color: 'orange'
                        border.color: 'pink'
                    }
                }
                RoundButton {
                    id: saveButton
                    Layout.fillHeight: true
                    Layout.preferredWidth: 150
                    radius: 0
                    text: qsTr('Save')

                    onClicked: saveItem()

                    background: Rectangle {
                        color: 'orange'
                        border.color: 'pink'
                    }
                }
                RoundButton {
                    id: deleteButton
                    Layout.fillHeight: true
                    Layout.preferredWidth: 150
                    radius: 0
                    text: qsTr('Discard')

                    onClicked: discardItem()

                    background: Rectangle {
                        color: 'orange'
                        border.color: 'pink'
                    }
                }

            }
        }
    }


    state: 'Normal'
    states: [
        State {
            name: 'Normal'
            PropertyChanges { target: widgetBox; enabled: false }
            PropertyChanges { target: buttonBox; enabled: true }
        }

    ]
}
