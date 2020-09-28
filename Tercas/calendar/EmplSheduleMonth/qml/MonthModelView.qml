import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import Wiipuri.Calendar 1.0

ListView {
    id: listView
    width: parent.width

    property int month: emplSheduleMonthModel.date.getMonth()
    property int daysInMonth: emplSheduleMonthModel.columnCount() - 1

    property int personCellWidth: 250
    property int delegateCellWidth: (listView.width - personCellWidth - daysInMonth * 3) / daysInMonth
    property int delegateCellHeight: 40

    spacing: 3
    clip: true
    model: emplSheduleMonthModel
    currentIndex: 0
    focus: true

    headerPositioning: ListView.OverlayHeader
    header: Rectangle {
        id: listHeader
        width: ListView.view.width
        height: headerLayout.height + 10
        color: root.color
        z: 2

        RowLayout {
            id: headerLayout
            anchors.top: parent.top
            spacing: 3
            Label {
                id: headerPersonLabel
                Layout.preferredWidth: listView.personCellWidth
                Layout.fillHeight: true
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                padding: 10
                font.bold: true
                font.pixelSize: 12
                color: "white"
                background: Rectangle { color: "#C05640" }
                text: qsTr("Работник")
            }

            // Delegates to show day of week and day number of month
            Repeater {
                model: daysInMonth
                delegate: ColumnLayout {

                    property date delegateDate: new Date(emplSheduleMonthModel.date.getFullYear(), emplSheduleMonthModel.date.getMonth(), index)
                    property string delegateDayOfWeekName: CalendarFunctions.getDayOfWeekNameAbbr(delegateDate.getDay())
                    property int delegateDayOfMonthNum: index + 1
                    property bool delegateIsDayOff: emplSheduleMonthModel.isDayOff(delegateDate)
                    property bool delegateIsHoliday: emplSheduleMonthModel.isHoliday(delegateDate)

                    Label {
                        Layout.preferredWidth: listView.delegateCellWidth
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        font.bold: delegateIsHoliday ? true : false
                        font.pixelSize: delegateIsHoliday ? 12 : 11
                        padding: 10
                        color: delegateIsDayOff ? "white" : "black"
                        background: Rectangle { color: (delegateIsDayOff || delegateIsHoliday) ? Qt.darker("#EDD170") : "#EDD170" }
                        text: delegateDayOfWeekName
                    }
                    Label {
                        Layout.preferredWidth: listView.delegateCellWidth
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        font.bold: true
                        font.pixelSize: 12
                        padding: 10
                        color: {
                            if (delegateIsHoliday)
                                return "red";
                            else
                                return delegateIsDayOff ? "white" : "black"
                        }
                        background: Rectangle { color: (delegateIsDayOff || delegateIsHoliday) ? Qt.darker("silver") : "silver" }
                        text: delegateDayOfMonthNum
                    }
                }
            }
        }
    }

    footerPositioning: ListView.OverlayFooter
    footer: Rectangle {
        id: listFooter
        width: ListView.view.width
        height: footerLayout.height + 3
        color: root.color
        z: 2

        RowLayout {
            id: footerLayout
            anchors.bottom: parent.bottom
            spacing: 3
            Label {
                Layout.preferredWidth: listView.personCellWidth
                Layout.fillHeight: true
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                padding: 10
                font.bold: true
                font.pixelSize: 12
                color: "white"
                background: Rectangle { color: "#0878A4" }
                text: qsTr("Количество работников\nна направлении")
            }
            Repeater {
                model: daysInMonth
                delegate: Label {

                    property date curDate: new Date(emplSheduleMonthModel.date.getFullYear(), emplSheduleMonthModel.date.getMonth(), index + 1)
                    property int personNumberAvailable: emplSheduleMonthModel.getNumberAvailable(modelData)
                    property int shiftNum: CalendarFunctions.getShiftNum(curDate)

                    Layout.preferredWidth: listView.delegateCellWidth
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.bold: true
                    font.pixelSize: 12
                    padding: 10
                    color: personNumberAvailable > 6 ? "black" : "red"
                    background: Rectangle { color: shiftNum === 4 ? "silver" : "transparent"; border.color: 'gray' }
                    text: shiftNum === 4 ? personNumberAvailable : ""
                }
            }
        }
    }

    delegate: Rectangle {
        id: delegateWrapper

        property int personPid: emplSheduleMonthModel.getPersonPid(index)

        width: listView.width
        height: listView.delegateCellHeight
        color: root.color

        RowLayout {
            spacing: 3
            Label {
                id: personCell
                Layout.preferredWidth: listView.personCellWidth
                Layout.preferredHeight: listView.delegateCellHeight
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.bold: true
                font.pixelSize: 12
                text: model.person
                background: Rectangle { color: "lightblue" }
            }
            Repeater {
                model: listView.daysInMonth
                Rectangle {
                    id: delegateRect

                    property date delegateDate: new Date(emplSheduleMonthModel.date.getFullYear(), emplSheduleMonthModel.date.getMonth(), index + 1)
                    property int delegateDayOfMonth: index + 1
                    property var dutyName: emplSheduleMonthModel.getAbbr(personPid, delegateDayOfMonth)

                    Layout.preferredWidth: listView.delegateCellWidth
                    Layout.fillHeight: true
//                    border.color: "lightgrey"
                    color: {
                        if (dutyName === 'опг') return 'lightgreen';
                        else if (dutyName === 'овг') return 'lightgreen';
                        else if (dutyName === 'осс') return 'green';
                        else if (dutyName === 'ксп') return 'orange';
                        else if (dutyName === 'eng') return 'yellow';
                        else if (dutyName === 'ref') return 'lightblue';
                        else if (dutyName === 'вых') return 'white';
                        else if (dutyName === 'окд') return 'lightgreen';
                        else if (dutyName === 'ТУ')  return 'lightblue';
                        else if (dutyName === 'бол') return 'red';
                        else if (dutyName === 'дор') return 'lightblue';
                        else if (dutyName === 'ком') return 'orange';
                        else if (dutyName === 'mls') return '#e1b746';
                        else if (dutyName === 'кпп') return 'orange';
                        else if (dutyName === 'кпс') return 'orange';
                        else if (dutyName === 'кпк') return 'orange';
                        else if (dutyName === 'крс') return 'orange';
                        else if (dutyName === 'пер') return 'lightblue';
                        else if (dutyName === 'крп') return 'orange';
                        else if (dutyName === 'субп') return 'yellow';
                        else if (dutyName === 'нсвп') return 'orange';
                        else if (dutyName === 'нстр') return 'orange';
                        else if (dutyName === 'нст2') return 'orange';
//                        else return Func.getShiftColor(delegateDate);
                        else (TercasDate.isShiftWorking(delegateDate, 4) ? Qt.lighter("yellow") : "transparent");
                    }
                    radius: 3

                    Label {
                        anchors.centerIn: parent
                        text: dutyName ? dutyName : '';
                    }


                    // ToolTip implementation for delegate
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            var component = Qt.createComponent("ToolTipPopup.qml")
                            if (component.status === Component.Ready) {
                                var tooltipText = emplSheduleMonthModel.getToolTip(personPid, delegateDayOfMonth)
                                if (tooltipText === undefined)
                                    return

                                var tooltipPopup = component.createObject(delegateRect, { "tooltipText" : tooltipText } )
                                tooltipPopup.open()
                            }
                        }
                    } // MouseArea

                }
            }
        }
    }

//    Keys.onDownPressed:   {
//                    if (listView.currentIndex + 1 < listView.count )
//                        listView.currentIndex += 1;
//                }
//                Keys.onUpPressed: {
//                    if (listView.currentIndex  >= 0)
//                        listView.currentIndex -= 1;
//                }

//    Keys.onPressed: console.log('OK')
}
