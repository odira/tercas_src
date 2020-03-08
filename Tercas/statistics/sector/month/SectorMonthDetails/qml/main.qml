import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQml.Models 2.12

import Wiipuri.Calendar 1.0
import Wiipuri.Models 1.0

ApplicationWindow {
    id: root
    width: Screen.width; height: Screen.height
    visible: true
    title: qsTr("Статистика загрузки секторов месячная (выборочные параметры)")

    property int year: 2019
    property int month: 0

    function setMonth(mon) {
        month = mon;
        browser.currentIndex = month
        browser.positionViewAtIndex(month, ListView.Contain)
    }

    header: RowLayout {
        id: header
        DatePicker {
            id: datePicker
            Layout.topMargin: 10
            Layout.alignment: Qt.AlignCenter
            showDate: false
            showMonth: false
            year: root.year
            month: root.month
            onYearChanged: root.year = year
            onMonthChanged: setMonth(month)
        }
    }

    Rectangle {
        id: central
        anchors.fill: parent

        DelegateModel {
            id: delegateModel
            model: 12; delegate: MonthDelegate { }
        }

        GridView {
            id: grid
            anchors.fill: parent
            cellWidth: width / 6; cellHeight: height / 2
            model: delegateModel.parts.grid
            interactive: true
            opacity: 1.0
            onCurrentIndexChanged: browser.positionViewAtIndex(currentIndex, ListView.Contain)
        }

        ListView {
            id: browser
            anchors.fill: parent
            model: delegateModel.parts.browser
            clip: true
            orientation: ListView.Horizontal
            snapMode: ListView.SnapOneItem
            highlightRangeMode: ListView.StrictlyEnforceRange
            interactive: false
            opacity: 0.0
            onCurrentIndexChanged: datePicker.month = currentIndex
        }

        state: 'inGrid'
        states: [
            State {
                name: "inGrid"
            },
            State {
                name: "inBrowser"
                PropertyChanges { target: grid; opacity: 0.0; interactive: false }
                PropertyChanges { target: browser; opacity: 1.0; interactive: true }
                PropertyChanges { target: datePicker; showMonth: true }
            }
        ]
    }


    footer: RowLayout {
        id: footer
        height: header.height
        Button {
            Layout.alignment: Qt.AlignRight
            Layout.rightMargin: 20
            text: qsTr("Close")
            onClicked: Qt.quit()
        }
    }
}
