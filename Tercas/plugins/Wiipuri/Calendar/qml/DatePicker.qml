import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "CalendarFuncs.js" as Func

Item {
    id: root
    width: mainLayout.width; height: mainLayout.height

    property var pickerDate: new Date()
    signal pickerDateUpdated(date newDate)

    property int date: pickerDate.getDate()
    property int month: pickerDate.getMonth()
    property int year: pickerDate.getFullYear()

    function daysInMonth (month, year) {
        return new Date(year, month, 0).getDate();
    }

    property bool showYear: true
    property bool showMonth: true
    property bool showDate: true

    TextMetrics {
        id: textMetrics
        text: 'A'
     }
    property var textSize: textMetrics.font.pixelSize * 2
    property var charWidth: (textMetrics.width + textMetrics.advanceWidth) * 2

    RowLayout {
        id: mainLayout
        anchors.margins: 5
        spacing: 3

        Frame {
            visible: showDate
            background: Rectangle {
                border.color: "black"
            }

            // Date block
            RowLayout {
                DirectionButton {
                    orientation: DirectionButton.Orientation.Previous
                    font: textMetrics.font
                    onClicked: {
                        date--
                        if (date === 0) {
                            month--
                            if (month === 0) {
                                month = 12
                                year--
                                pickerDate.setFullYear(year)
                            }
                            pickerDate.setMonth(month)
                            var maxDateInMonth = daysInMonth(month, year)
                            date = maxDateInMonth
                        }
                        pickerDate.setDate(date)

                        pickerDateUpdated(pickerDate)
                    }
                }
                TextArea {
                    id: textDate
                    implicitWidth: charWidth * 1.5
                    font.pixelSize: textSize
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    readOnly: true
                    text: date
                }
                DirectionButton {
                    orientation: DirectionButton.Orientation.Next
                    onClicked: {
                        date++
                        var maxDateInMonth = daysInMonth(month, year)
                        if (date > maxDateInMonth) {
                            date = 1
                            month++
                            if (month === 12) {
                                month = 0
                                year++
                                pickerDate.setFullYear(year)
                            }
                            pickerDate.setMonth(month)
                        }
                        pickerDate.setDate(date)

                        pickerDateUpdated(pickerDate)
                    }
                }
            }
        }

        // Month block
        Frame {
            visible: showMonth
            background: Rectangle {
                border.color: "black"
            }

            RowLayout {
                DirectionButton {
                    orientation: DirectionButton.Orientation.Previous
                    font: textMetrics.font
                    onClicked: {
                        month--
                        if (month === -1) {
                            month = 11
                            year--
                            pickerDate.setFullYear(year)
                        }
                        pickerDate.setMonth(month)

                        var maxDateInMonth = daysInMonth(month, year)
                        if (date > maxDateInMonth) {
                            date = maxDateInMonth
                            pickerDate.setDate(date)
                        }

                        pickerDateUpdated(pickerDate)
                    }
                }
                TextArea {
                    implicitWidth: charWidth * 6
                    font.pixelSize: textSize
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    readOnly: true
                    text: Func.getMonthName0(month) + ' - (' + (month +1) + ')'
                }
                DirectionButton {
                    orientation: DirectionButton.Orientation.Next
                    onClicked: {
                        month++
                        if (month === 12) {
                            month = 0
                            year++
                            pickerDate.setFullYear(year)
                        }

                        pickerDate.setMonth(month)
                        var maxDateInMonth = daysInMonth(month, year)
                        if (date > maxDateInMonth) {
                            date = maxDateInMonth
                            pickerDate.setDate(date)
                        }

                        pickerDateUpdated(pickerDate)
                    }
                }
            }
        }

        // Year block
        Frame {
            visible: showYear
            background: Rectangle {
                border.color: "black"
            }

            RowLayout {
                DirectionButton {
                    orientation: DirectionButton.Orientation.Previous
                    font: textMetrics.font
                    onClicked: {
                        year--
                        pickerDate.setFullYear(year)

                        var maxDateInMonth = daysInMonth(month, year)
                        if (date > maxDateInMonth) {
                            date = maxDateInMonth
                            pickerDate.setDate(date)
                        }

                        pickerDateUpdated(pickerDate)
                    }
                }
                TextArea {
                    implicitWidth: charWidth * 2.5
                    font.pixelSize: textSize
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    readOnly: true
                    text: year
                }
                DirectionButton {
                    orientation: DirectionButton.Orientation.Next
                    onClicked: {
                        year++
                        pickerDate.setFullYear(year)

                        var maxDateInMonth = daysInMonth(month, year)
                        if (date > maxDateInMonth) {
                            date = maxDateInMonth
                            pickerDate.setDate(date)
                        }

                        pickerDateUpdated(pickerDate)
                    }
                }
            }
        }
    }
}
