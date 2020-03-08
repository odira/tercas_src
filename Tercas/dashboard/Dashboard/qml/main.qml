import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQml.Models 2.12

import Wiipuri.Process 1.0

ApplicationWindow {
    id: rootWindow
    title: qsTr("TERCAS DashBoard")
    width: 1400; height: 800
    color: "#d5d6d8"
    visible: true
    visibility: {
        if (Qt.platform.os === "linux")
            return "Maximized";
        else if (Qt.platform.os === "osx")
            return "Windowed";
        else
            return "Maximized";
    }

    Process { id: process }

    Component {
        id: appDelegate
        Rectangle {
            width: 200; height: 300
            color: 'transparent'
            ColumnLayout {
                anchors.fill: parent
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: 'lightblue'
                }
                Label {
                    Layout.fillWidth: true
                    height: 50
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    font.bold: true
                    text: appTag
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var appPath = '/usr/local/bin/vyborg/statistics/' + appName + '.app/Contents/MacOS/' + appName
                    process.start(appPath)
                }
            }
        }
    }

    ColumnLayout {
        anchors { fill: parent; margins: 10 }
        spacing: 10

        TabBar {
            id: bar
            Layout.fillWidth: true
            TabButton { font.bold: true; text: qsTr('Статистика') }
            TabButton { font.bold: true; text: qsTr('Расписание') }
            TabButton { font.bold: true; text: qsTr('Безопасность полетов') }
        }
        StackLayout {
            id: stack
            Layout.alignment: Qt.AlignCenter
            currentIndex: bar.currentIndex
            Item {
                id: statisticsTab
                ListModel {
                    id: statisticsModel
                    ListElement { appTag: qsTr('Часовая загрузка\nпо секторам'); appName: 'SectorHour' }
                    ListElement { appTag: qsTr('Суточная загрузка\nпо секторам'); appName: 'SectorDay' }
                    ListElement { appTag: qsTr('Месячная загрузка\nпо секторам'); appName: 'SectorMonth' }
                    ListElement { appTag: qsTr('Месячная загрузка\nпо секторам (детализация)'); appName: 'SectorMonthDetails' }
                }
                RowLayout {
                    Layout.fillWidth: true
                    Layout.margins: 10
                    spacing: 10
                    Repeater {
                        model: statisticsModel
                        delegate: appDelegate
                    }
                }
            }
            Item {
                id: calendarTab
                ListModel {
                    id: calendarModel
                    ListElement { appTag: qsTr('Годовой календарь\nсмен'); appName: 'ATCcal' }
                    ListElement { appTag: qsTr('Календарь направления\nпо месяцам'); appName: 'EmplSheduleMonth' }
                    ListElement { appTag: qsTr('Управление\nкалендарем'); appName: 'emplcalendarperiodQt' }
                }
                RowLayout {
                    Layout.fillWidth: true
                    Layout.margins: 10
                    spacing: 10
                    Repeater {
                        model: calendarModel
                        delegate: appDelegate
                    }
                }
            }
            Item {
                id: safetyTab
                ListModel {
                    id: safetyModel
                    ListElement { appTag: qsTr('База данных\nавиационных событий'); appName: 'Safety' }
                }
                RowLayout {
                    Layout.fillWidth: true
                    Layout.margins: 10
                    spacing: 10
                    Repeater {
                        model: safetyModel
                        delegate: appDelegate
                    }
                }
            }
        }
        RowLayout {
            id: buttonBox
            Layout.alignment: Qt.AlignRight
            spacing: 10
            Button {
                id: backButton
                font.bold: true
                text: qsTr('Back')
                visible: Qt.platform.os !== "android"
            }
            Button {
                id: quitButton
                font.bold: true
                text: qsTr('Quit')
                onClicked: Qt.quit()
            }
        }
    }
}
