import QtQuick 2.6
import QtQml.Models 2.2
import QtQuick.Window 2.0

Rectangle {
    id: root

    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight
    antialiasing: true

    property alias currentIndex: pageView.currentIndex

    Rectangle {
        id: banner

        height: bannerColumnContent.implicitHeight + 20
        anchors.top: parent.top
        width: parent.width
        color: "#e07a2e"

//        Image {
//            id: arrow

//            source: "qrc:///images/icon-left-arrow.png"
//            anchors.left: banner.left
//            anchors.leftMargin: 20
//            anchors.verticalCenter: banner.verticalCenter
//            visible: root.currentIndex === 1 ? true : false

//            MouseArea {
//                anchors.fill: parent
//                onClicked: root.currentIndex = 0;
//            }
//        }
        Column {
            id: bannerColumnContent

            anchors.fill: parent
            anchors.margins: 10
            spacing: 5

            Text {
                color: "white"
                font.family: "Abel"
                font.pointSize: 20
                text: "Безопасность полетов"
            }
            Text {
                color: "white"
                font.pointSize: 12
                text: "База данных авиационных событий и инцидентов"
            }
        }
    }
    ListView {
        id: pageView

        width: parent.width
        anchors.top: banner.bottom
        anchors.bottom: parent.bottom
        snapMode: ListView.SnapOneItem
        highlightMoveDuration: 200
        flickDeceleration: 2000
        focus: true
        orientation: ListView.Horizontal
        boundsBehavior: Flickable.StopAtBounds
        cacheBuffer: 200
        preferredHighlightBegin: 0; preferredHighlightEnd: 0

        model: ObjectModel {
            ListPage {
                id: listPage
                width: pageView.width / 3
                height: pageView.height
            }
            ItemPage {
                id: itemPage
                width: pageView.width / 3
                height: pageView.height
                currentIndex: listPage.currentIndex
            }
            MapPage {
                id: mapPage
                width: pageView.width / 3
                height: pageView.height
            }
        }
    }
}
