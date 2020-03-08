import QtQuick 2.12
import QtQuick.Controls 2.2
import QtQuick.Window 2.0
//import QtQml.Models 2.2
import QtQuick.Layouts 1.3

import WiiCalendar 1.0


ApplicationWindow {
    id: root
    width: Screen.width
    height: Screen.height
    title: qsTr("Terkas Calendar")
    visible: true

    property date currentDate: new Date
    property int year: currentDate.getFullYear()
    property int month: currentDate.getMonth()
    property int date: currentDate.getDate()
    property int shift: 4

    /* Выползающее меню
     * */
    OptionsDrawer {
        id: optionsDrawer

        width: 0.3 * root.width
        height: root.height

        shift: root.shift
        onShiftChanged: root.shift = shift
    }

    /* HEADER
     */
    header: ToolBar {
        RowLayout {
            anchors.left: parent.left
            anchors.leftMargin: 20
            height: parent.height
            spacing: 20

            ToolButton {
                id: leftArrowButton

                height: parent.height

                Image {
                    height: parent.height - 10
                    anchors.centerIn: parent
                    fillMode: Image.PreserveAspectFit
                    smooth: true
                    source: "qrc:/images/icon-left-arrow.png"
                }
                onClicked: {
                    if (calendarStack.state === "yearCalendar")
                        root.year--;
                    else if (calendarStack.state === "monthCalendar")
                        root.month--;
                    else if (calendarStack.state === "dateCalendar")
                        root.date--;
                }
            }
            Label {
                id: yearLabel
                text: root.year
                font.pixelSize: 20
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: false
                Layout.alignment: Qt.AlignLeft
                visible: true
            }
            Label {
                id: monthLabel
                width: 300
                text: Func.getMonthName(root.month)
                font.pixelSize: 20
                elide: Label.ElideMiddle
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: false
                Layout.alignment: Qt.AlignLeft
                visible: false
            }
            Label {
                id: dayLabel
                text: root.date
                font.pixelSize: 20
                elide: Label.ElideMiddle
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: false
                Layout.alignment: Qt.AlignLeft
                visible: false
            }
            ToolButton {
                id: rightArrowButton

                height: parent.height

                Image {
                    height: parent.height - 10
                    anchors.centerIn: parent
                    fillMode: Image.PreserveAspectFit
                    rotation: 180
                    smooth: true
                    source: "qrc:/images/icon-left-arrow.png"
                }
                onClicked: {
                    if (calendarStack.state === "yearCalendar")
                        root.year++;
                    else if (calendarStack.state === "monthCalendar")
                        root.month == 11 ? (root.month = 0, root.year++)
                                         : root.month++;
                    else if (calendarStack.state === "dateCalendar")
                        root.date++;
                }
            }
        }
        RowLayout {
            anchors.right: parent.right
            anchors.rightMargin: 20
            height: parent.height
            spacing: 20

            Label {
                id: shiftLabel

                text: qsTr("смена №") + root.shift
                font.pixelSize: 20
                elide: Label.ElideMiddle
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: false
                Layout.rightMargin: 0
                visible: true
            }
        }
    }

    /* FOOTER
     */
    footer: ToolBar {
        height: backImage.height + 10

        RowLayout {
            ToolButton {
                contentItem: Image {
                    id: backImage

                    fillMode: Image.PreserveAspectFit
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    rotation: 180
                    source: "qrc:/images/arrow.png"
                }
                onClicked: calendarStack.currentIndex--;
            }
        }
        RowLayout {
            anchors.right: parent.right
            height: parent.height
            spacing: 20

            ToolButton {
                height: parent.height

                contentItem: Image {
                    id: drawerImage

                    sourceSize.height: backImage.height
                    fillMode: Image.PreserveAspectFit
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    Layout.fillWidth: false
                    Layout.alignment: Qt.AlignRight
                    source: "qrc:/images/drawer.png"
                }
                onClicked: optionsDrawer.open();
            }
        }
    }

    /* Main STACK widget
     */
    StackLayout {
        id: calendarStack
        anchors.fill: parent

        YearPage  { }
        MonthPage { }
        DatePage  { }

        onCurrentIndexChanged: {
            if (currentIndex === 0)
                calendarStack.state = "yearCalendar";
            else if (currentIndex === 1)
                calendarStack.state = "monthCalendar";
            else if (currentIndex === 2)
                calendarStack.state = "dateCalendar";
        }

        state: "yearCalendar"
        states: [
            State {
                name: "yearCalendar"
                PropertyChanges { target: backImage; visible: false }
                PropertyChanges { target: calendarStack; currentIndex: 0 }
                PropertyChanges { target: monthLabel; visible: false }
                PropertyChanges { target: dayLabel; visible: false }
            },
            State {
                name: "monthCalendar"
                PropertyChanges { target: backImage; visible: true }
                PropertyChanges { target: calendarStack; currentIndex: 1 }
                PropertyChanges { target: monthLabel; visible: true }
                PropertyChanges { target: dayLabel; visible: false }
            },
            State {
                name: "dateCalendar"
                PropertyChanges { target: backImage; visible: true }
                PropertyChanges { target: calendarStack; currentIndex: 2 }
                PropertyChanges { target: monthLabel; visible: true }
                PropertyChanges { target: dayLabel; visible: true }
            }
        ]
    }
}
