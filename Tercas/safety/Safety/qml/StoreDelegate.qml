import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Component {
    id: storeDelegate
    Package {

        Item {
            id: fullscreenItem
            Package.name: 'fullscreen'
            width: rootWindow.width; height: rootWindow.height

            Rectangle {
                anchors.fill: parent
                color: "red"

                Text {
                    anchors.centerIn: parent
                    text: model._1
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    listView.currentIndex = index
                    listView.enabled = true
                    listView.opacity = 1.0
                    fullscreenView.enabled = false
                    fullscreenView.opacity = 0.0
                }
            }
        }

        Item {
            id: listItem
            Package.name: 'list'
            width: rootWindow.width; height: 50

            Rectangle {
                anchors.fill: parent
                anchors.margins: 10
                color: "lightyellow"

                Text {
                    anchors.centerIn: parent
                    text: model._1
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    fullscreenView.currentIndex = index
                    fullscreenView.enabled = true
                    fullscreenView.opacity = 1.0
                    listView.enabled = false
                    listView.opacity = 0.0
                }
            }
        }
    }
}
