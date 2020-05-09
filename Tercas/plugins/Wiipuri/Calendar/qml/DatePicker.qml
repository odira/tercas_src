import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "CalendarFuncs.js" as Func

Item {
    id: datePicker

    // Variables for calendar
    property var dpDate: new Date()
    signal dpDateUpdated(date newDate)

    property int date: dpDate.getDate()
    property int month: dpDate.getMonth()
    property int year: dpDate.getFullYear()

    function daysInMonth (month, year) {
        return new Date(year, month, 0).getDate();
    }

    // GRAPHICS

    // Variables for graphics
    property bool showYear: true
    property bool showMonth: true
    property bool showDate: true

    TextMetrics {
        id: textMetrics
        text: 'A'
    }
    property var textSize: textMetrics.font.pixelSize * 1.3
    property var charWidth: (textMetrics.width + textMetrics.advanceWidth) * 1.3

    // Variables for DirectionButton items
    property int directionButtonWidth: 50
    property int directionButtonHeight: directionButtonWidth
    property var directionButtonFont: textMetrics.font

    // Variables for blocks
    property color monthBlockColor: Qt.lighter("blue")
    property color yearBlockColor: Qt.lighter("green")

    // Spacer item
    Component {
        id: spacer
        Rectangle {
            width: 2
            Layout.fillHeight: true
            color: "gray"
        }
    }

    Row {
        id: root
        spacing: 2

        Loader { height: datePicker.height; sourceComponent: spacer }

//        // DATE block
//        Frame {
//            id: dateFrame

//            Layout.fillHeight: true
//            visible: showDate

//            RowLayout {
//                DirectionButton {
//                    orientation: DirectionButton.Orientation.Previous
//                    onClicked: {
//                        date--
//                        if (date === 0) {
//                            month--
//                            if (month === 0) {
//                                month = 12
//                                year--
//                                dpDate.setFullYear(year)
//                            }
//                            dpDate.setMonth(month)
//                            var maxDateInMonth = daysInMonth(month, year)
//                            date = maxDateInMonth
//                        }
//                        dpDate.setDate(date)

//                        dpDateUpdated(dpDate)
//                    }
//                }

//                TextArea {
//                    id: textDate

//                    background: Rectangle {
//                        color: "yellow"
//                    }

//                    implicitWidth: charWidth * 1.5
//                    font.pixelSize: textSize
//                    verticalAlignment: Text.AlignVCenter
//                    horizontalAlignment: Text.AlignHCenter
//                    readOnly: true
//                    text: date
//                }

//                DirectionButton {
//                    orientation: DirectionButton.Orientation.Next
//                    onClicked: {
//                        date++
//                        var maxDateInMonth = daysInMonth(month, year)
//                        if (date > maxDateInMonth) {
//                            date = 1
//                            month++
//                            if (month === 12) {
//                                month = 0
//                                year++
//                                dpDate.setFullYear(year)
//                            }
//                            dpDate.setMonth(month)
//                        }
//                        dpDate.setDate(date)

//                        dpDateUpdated(dpDate)
//                    }
//                }
//            }
//        }

        // MONTH block
        Frame {
            id: monthBlock
            visible: showMonth

            RowLayout {
                anchors.fill: parent

                DirectionButton {
                    orientation: DirectionButton.Orientation.Previous
                    color: monthBlockColor
                    onClicked: {
                        month--
                        if (month === -1) {
                            month = 11
                            year--
                            dpDate.setFullYear(year)
                        }
                        dpDate.setMonth(month)

                        var maxDateInMonth = daysInMonth(month, year)
                        if (date > maxDateInMonth) {
                            date = maxDateInMonth
                            dpDate.setDate(date)
                        }

                        dpDateUpdated(dpDate)
                    }
                }

                TextArea {
                    Layout.fillHeight: true
                    implicitWidth: charWidth * 6
                    font.pixelSize: textSize
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    readOnly: true
                    text: Func.getMonthName0(month) + ' - (' + (month +1) + ')'
                    background: Rectangle {
                        height: 50
                        color: "transparent"
                        border.color: monthBlockColor
                    }
                }

                DirectionButton {
                    orientation: DirectionButton.Orientation.Next
                    color: monthBlockColor
                    onClicked: {
                        month++
                        if (month === 12) {
                            month = 0
                            year++
                            dpDate.setFullYear(year)
                        }

                        dpDate.setMonth(month)
                        var maxDateInMonth = daysInMonth(month, year)
                        if (date > maxDateInMonth) {
                            date = maxDateInMonth
                            dpDate.setDate(date)
                        }

                        dpDateUpdated(dpDate)
                    }
                }
            }
        }

        // YEAR block
        Frame {
            id: yearFrame
            visible: showYear

            RowLayout {
                anchors.fill: parent

                DirectionButton {
                    orientation: DirectionButton.Orientation.Previous
                    color: yearBlockColor
                    onClicked: {
                        year--
                        dpDate.setFullYear(year)

                        var maxDateInMonth = daysInMonth(month, year)
                        if (date > maxDateInMonth) {
                            date = maxDateInMonth
                            dpDate.setDate(date)
                        }

                        dpDateUpdated(dpDate)
                    }
                }

                TextArea {
                    Layout.fillHeight: true
                    implicitWidth: charWidth * 3
                    font.pixelSize: textSize
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    readOnly: true
                    text: year
                    background: Rectangle {
                        height: 50
                        color: "transparent"
                        border.color: yearBlockColor
                    }
                }

                DirectionButton {
                    orientation: DirectionButton.Orientation.Next
                    color: yearBlockColor
                    onClicked: {
                        year++
                        dpDate.setFullYear(year)

                        var maxDateInMonth = daysInMonth(month, year)
                        if (date > maxDateInMonth) {
                            date = maxDateInMonth
                            dpDate.setDate(date)
                        }

                        dpDateUpdated(dpDate)
                    }
                }
            }
        }

        Loader { Layout.fillHeight: true; sourceComponent: spacer }
    }
}
