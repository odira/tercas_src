import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import RestrictionModel 1.0

Page {
    id: restrictionPage

    property int currentRestriction: -1

    RestrictionDialog {
        id: restrictionDialog

        onFinished: {
            if (currentRestriction === -1)
                restrictionListView.model.append(ad, indxMil, callSign, zone, levelFrom, levelTo, timeFrom, timeTo, note);
            else
                restrictionListView.model.set(currentRestriction,
                                              ad, indxMil, callSign, zone, levelFrom, levelTo, timeFrom, timeTo, note);
        }
    }

//    header: Rectangle {
//        width: parent.width
//        height: headerText.height + 20
//        color: "transparent"

//        RowLayout {
//            anchors.fill: parent
//            anchors.margins: 10
//            spacing: 10

//            Rectangle {
//                height: parent.height
//                Layout.fillWidth: true
//                radius: 10
//                border.color: "orange"
//                color: "transparent"
//            }
//            Rectangle {
//                height: parent.height
//                Layout.fillWidth: true
//                Layout.alignment: Qt.AlignRight
//                radius: 10
//                border.color: "orange"
//                color: "transparent"
//            }
//        }
//    }

    contentItem: ListView {
        id: restrictionListView
        focus: true
        boundsBehavior: Flickable.StopAtBounds
        clip: true
        spacing: 10
        model: RestrictionModel { }
        delegate: RestrictionDelegate {
            width: parent.width

            MouseArea {
                anchors.fill: parent
                onPressAndHold: {
                    currentRestriction = index;
                    delegateMenu.open();
                }
            }
        }
    }

    footer: Rectangle {
        id: footerContext
        width: parent.width
        height: addButton.height + 20
        color: "transparent"

        Button {
            id: addButton
            anchors.centerIn: parent
            width: parent.width / 2

            contentItem: Text {
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 18
                font.bold: true
                color: "white"
                text: qsTr("Добавить")
            }

            background: Rectangle {
                radius: 10
                color: "green"
            }

            onClicked: {
                currentRestriction = -1;
                addMenu.open();
            }
        }
    }

    Menu {
        id: addMenu
        parent: restrictionPage
        x: (restrictionPage.width - width) / 2
        y: (restrictionPage.height - height) / 2
        modal: true
        font.pixelSize: 18

        Label {
            padding: 10
            color: "green"
            width: parent.width
            horizontalAlignment: Qt.AlignHCenter
            text: qsTr("Добавить")
        }
        MenuItem {
            text: qsTr("Ограничение")
            onTriggered: restrictionDialog.createRestriction();
        }
        MenuItem {
            text: qsTr("Перелет")
        }
        MenuItem {
            text: qsTr("Другое")
        }
    }

    Menu {
        id: delegateMenu
        parent: restrictionPage
        x: (restrictionPage.width - width) / 2
        y: (restrictionPage.height - height) / 2
        modal: true
        font.pixelSize: 18

        Label {
            padding: 10
            color: "red"
            width: parent.width
            horizontalAlignment: Qt.AlignHCenter
            text: currentRestriction >= 0 ? restrictionListView.model.get(currentRestriction).ad : ""
        }
        MenuItem {
            text: qsTr("Редактировать...")
            onTriggered: restrictionDialog.editRestriction(restrictionListView.model.get(currentRestriction));
        }
        MenuItem {
            text: qsTr("Удалить")
            onTriggered: restrictionListView.model.remove(currentRestriction);
        }
    }
}
