import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "CalendarFuncs.js" as Func

Item {
    id: root
    width: mainLayout.width; height: mainLayout.height

    property var datePicker: new Date()
    signal datePickerUpdated(date newDate)

    property int date: datePicker.getDate()
    property int month: datePicker.getMonth()
    property int year: datePicker.getFullYear()

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
    property var textSize: textMetrics.font.pixelSize * 1.5
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

            // DATE block
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
                                datePicker.setFullYear(year)
                            }
                            datePicker.setMonth(month)
                            var maxDateInMonth = daysInMonth(month, year)
                            date = maxDateInMonth
                        }
                        datePicker.setDate(date)

                        datePickerUpdated(datePicker)
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
                                datePicker.setFullYear(year)
                            }
                            datePicker.setMonth(month)
                        }
                        datePicker.setDate(date)

                        datePickerUpdated(datePicker)
                    }
                }
            }
        }

        // MONTH block
        Frame {
            id: monthFrame

            property var frameColor: "blue"

            visible: showMonth
            background: Rectangle {
                border.color: monthFrame.frameColor
                radius: 2
            }

            RowLayout {
                DirectionButton {
                    orientation: DirectionButton.Orientation.Previous
                    font: textMetrics.font
                    buttonColor: monthFrame.frameColor
                    onClicked: {
                        month--
                        if (month === -1) {
                            month = 11
                            year--
                            datePicker.setFullYear(year)
                        }
                        datePicker.setMonth(month)

                        var maxDateInMonth = daysInMonth(month, year)
                        if (date > maxDateInMonth) {
                            date = maxDateInMonth
                            datePicker.setDate(date)
                        }

                        datePickerUpdated(datePicker)
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
                    buttonColor: monthFrame.frameColor
                    onClicked: {
                        month++
                        if (month === 12) {
                            month = 0
                            year++
                            datePicker.setFullYear(year)
                        }

                        datePicker.setMonth(month)
                        var maxDateInMonth = daysInMonth(month, year)
                        if (date > maxDateInMonth) {
                            date = maxDateInMonth
                            datePicker.setDate(date)
                        }

                        datePickerUpdated(datePicker)
                    }
                }
            }
        }

        // Year block
        Frame {
            id: yearFrame

            property var frameColor: "green"

            visible: showYear
            background: Rectangle {
                border.color: yearFrame.frameColor
                radius: 2
            }

            RowLayout {
                DirectionButton {
                    orientation: DirectionButton.Orientation.Previous
                    font: textMetrics.font
                    buttonColor: yearFrame.frameColor
                    onClicked: {
                        year--
                        datePicker.setFullYear(year)

                        var maxDateInMonth = daysInMonth(month, year)
                        if (date > maxDateInMonth) {
                            date = maxDateInMonth
                            datePicker.setDate(date)
                        }

                        datePickerUpdated(datePicker)
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
                    buttonColor: yearFrame.frameColor
                    onClicked: {
                        year++
                        datePicker.setFullYear(year)

                        var maxDateInMonth = daysInMonth(month, year)
                        if (date > maxDateInMonth) {
                            date = maxDateInMonth
                            datePicker.setDate(date)
                        }

                        datePickerUpdated(datePicker)
                    }
                }
            }
        }
    }
}
