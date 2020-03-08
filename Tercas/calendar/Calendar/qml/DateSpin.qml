import QtQuick 2.5
import QtQuick.Controls 2.0

Item {
    id: dateSpin

    width: row.width
    height: 200

    property int year
    property int month
    property int date

    signal yearValChanged(int year)

    function showMonthLabel (vis) {
        monthLabel.visible = vis;
    }
    function showDateLabel (vis) {
        dateLabel.visible = vis;
    }

    Row {
        id: row

        height: parent.height
        spacing: 25

        Image {
            id: leftArrow

            height: parent.height - 10
            anchors.verticalCenter: parent.verticalCenter
            fillMode: Image.PreserveAspectFit
            rotation: 270
            smooth: true
//            source: "qrc:/images/triangle.png"
            source: "qrc:icon-left-arrow"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    year--;
                    yearValChanged(year);
                }
            }
        }
        Label {
            id: yearLabel

            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 30
            font.bold: true
            color: "darkblue"
            text: year
        }
        Label {
            id: monthLabel

            anchors.verticalCenter: parent.verticalCenter
            visible: false
            font.pixelSize: 30
            font.bold: true
            color: "darkblue"
            text: month + 1
        }
        Label {
            id: dateLabel

            anchors.verticalCenter: parent.verticalCenter
            visible: false
            font.pixelSize: 30
            font.bold: true
            color: "darkblue"
            text: date
        }
        Image {
            id: rightArrow

            height: parent.height - 10
            anchors.verticalCenter: parent.verticalCenter
            fillMode: Image.PreserveAspectFit
            rotation: 90
            smooth: true
//            source: "qrc:/images/triangle.png"
            source: "qrc:icon-left-arrow"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    year++;
                    yearValChanged(year);
                }
            }
        }
    }

//    states: [
//        State {
//            name: "year"
//            PropertyChanges {
//                target: leftArrow

//            }
//        }
//    ]
}
