import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.calendar 1.0

//import WiiCalendar 1.0
import Wiipuri.Calendar 1.0

Page {
    id: page
    title: qsTr("Годовой календарь")

    property int year: new Date().getFullYear()
    property int shiftNum: 4

    GridView {
        id: calendarGrid
        anchors.fill: parent
        anchors.margins: 2
        cellWidth: width / 4
        cellHeight: height / 3
        delegate: calendarDelegate

        Component {
            id: calendarDelegate

            Rectangle {
                width: calendarGrid.cellWidth - 20
                height: calendarGrid.cellHeight - 20
                border.color: "gray"
                antialiasing: true

                GridLayout {
                    anchors.fill: parent
                    anchors.margins: 5
                    columns: 1
                    rows: 3

                    Label {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Layout.minimumHeight: 30
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        height: 40
                        background: Rectangle { color: "lightblue" }
                        font.bold: true
                        color: "white"
                        text: Func.getMonthName0(model.month)
                    }

                    DayOfWeekRow {
                        locale: monthGridControl.locale
                        Layout.fillWidth: true
                    }

                    MonthGrid {
                        id: monthGridControl
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        locale: Qt.locale("ru_RU")
                        month: model.month
                        year: model.year


                        delegate: Label {
                            id: delegate

                            property date currentDate: new Date(model.year, model.month, model.day)
//                            property int shiftNum: Func.getShiftNum(plainDate)

                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter

                            background: Rectangle {
                                border.color: {
                                    model.month === monthGridControl.month ?
                                                  "steelblue"
                                                  : "lightgray"
                                }
                                color: {
                                    var theColor = "transparent"

                                    // Стилизуем отображение текущей даты
                                    if (model.today) {
                                        theColor = "lightblue"
                                        return theColor
                                    }

                                    // Стилизуем отображение рабочих дней смен
                                    TercasDate.isShiftWorking(currentDate, 4) === true ?
                                                theColor = Qt.lighter("orange")
                                              : theColor = "transparent"

                                    return theColor
                                }
                            }
                            opacity: model.month === monthGridControl.month ? 1 : 0.3
                            text: model.day
                            color: model.today ? "blue" : "black"
                            font.bold: model.today ? true : false

                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    console.log(model.date.getMonth())
                                }
                            }
                        }
                    }
                }
            }
        }

        model: CalendarModel {
            from: new Date(year, 0, 1)
            to: new Date(year, 11, 31)
        }
    }
}
