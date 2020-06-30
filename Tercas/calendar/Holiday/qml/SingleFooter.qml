import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RowLayout {
    id: singleButtonBox

    Layout.alignment: Qt.AlignHCenter

    property color buttonBackground: "#8EC9BB"

    function edit() {
        singleView.contentItem.children[singleView.currentIndex].state = 'Edit'
        singleButtonBox.state = 'Edit'
    }
    function discard() {
        singleView.contentItem.children[singleView.currentIndex].state = 'Normal'
        singleButtonBox.state = 'Normal'
    }

    RoundButton {
        id: editButton
        Layout.fillHeight: true
        Layout.preferredWidth: 150
        radius: 0
        text: qsTr('Edit')
        font.bold: true

        onClicked: edit()

        background: Rectangle {
            color: buttonBackground
            border.color: 'pink'
        }
    }
    RoundButton {
        id: saveButton
        Layout.fillHeight: true
        Layout.preferredWidth: 150
        radius: 0
        text: qsTr('Save')
        font.bold: true

        onClicked: save()

        background: Rectangle {
            color: buttonBackground
            border.color: 'pink'
        }
    }
    RoundButton {
        id: discardButton
        Layout.fillHeight: true
        Layout.preferredWidth: 150
        radius: 0
        text: qsTr('Discard')
        font.bold: true

        onClicked: discard()

        background: Rectangle {
            color: buttonBackground
            border.color: 'pink'
        }
    }

    state: 'Normal'
    states: [
        State {
            name: 'Normal'
            PropertyChanges { target: editButton; enabled: true }
            PropertyChanges { target: saveButton; enabled: false }
            PropertyChanges { target: discardButton; enabled: false }
        },
        State {
            name: 'Edit'
            PropertyChanges { target: editButton; enabled: false }
            PropertyChanges { target: saveButton; enabled: true }
            PropertyChanges { target: discardButton; enabled: true }
        }
    ]
}
