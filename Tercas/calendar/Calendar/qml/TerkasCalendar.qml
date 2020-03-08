import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4

import WiiCalendar 1.0

Calendar {
    id: calendar

    // Built-in properties:
    // visibleYear
    // visibleMonth
    property int shiftNum

    TercasDate {
        id: tDate
    }

    style: CalendarStyle {

        navigationBar: Rectangle {
            visible: (calendarStack.state === 'monthCalendar') ? false : true
            height: 24
            color: "lightblue"

            /* Горизонтальный разделитель,
             * который отделяет navigationBar от поля с  числами
             * */
            Rectangle {
                color: "#d7d7d7"
                height: 1
                width: parent.width
                anchors.bottom: parent.bottom
            }

            /* Помещаем стилизованный Label
             * */
            Label {
                id: dateText
                text: Func.getMonthName0(calendar.visibleMonth)
                color: "blue"
                font.bold: true
                elide: Text.ElideRight
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 12
                anchors.fill: parent
            }
        }

        /* Стилизуем отображением квадратиков с числами месяца
         * */
        dayDelegate: Rectangle {
            anchors.fill: parent
            anchors.margins: styleData.selected ? -1 : 0
            color: {
                var theColor = "transparent"

                if (styleData.date !== undefined) {
//                    if (styleData.selected && styleData.visibleMonth === root.month) {
                    if (styleData.date.toLocaleDateString() === root.currentDate.toLocaleDateString())
                        theColor = selectedDateColor
                    else {
                        /* Стилизуем отображение рабочих дней смен
                         * */
                        tDate.date = styleData.date;
                        var jDate = (tDate.julianDay() + shiftNum) % 6
                        if (jDate === 0 || jDate === 1 || jDate === 2) {
                            theColor = Qt.lighter("orange")
                        }
                    }
                }

                return theColor;
            }

            /* Задаём предопределённые переменные с цветами, доступные только для чтения
             * */
            readonly property color sameMonthDateTextColor: "#444"
            readonly property color selectedDateColor: "#34aadc"
            readonly property color selectedDateTextColor: "white"
            readonly property color differentMonthDateTextColor: "#bbb"
            readonly property color invalidDateColor: "#dddddd"

            // Помещаем Label для отображения числа
            Label {
                id: dayDelegateText

                text: styleData.date.getDate() // Устанавливаем число в текущий квадрат
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignRight
                font.pixelSize: styleData.valid && styleData.visibleMonth ? 11 : 8
                font.bold: styleData.valid && styleData.visibleMonth ? true : false

                // Установка цвета
                color: {
                    var theColor = invalidDateColor; // Устанавливаем невалидный цвет текста
                    if (styleData.valid) {
                        /* Определяем цвет текста в зависимости от того
                         * относится ли дата к выбранному месяцу или нет
                         * */
                        theColor = styleData.visibleMonth ? sameMonthDateTextColor : differentMonthDateTextColor;

                        if (styleData.selected) {
                            // Перекрашиваем цвет текста, если выбрана данная дата в календаре
                            theColor = selectedDateTextColor;
                        }
                    }
                    theColor;
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (styleData.visibleMonth) {
                        root.date = styleData.date.getDate();
                        calendarStack.state = "dateCalendar";
                    }
                }
            }
        }
    }
}
