import QtQuick 2.9
import QtQuick.Controls 2.2


SectionPage {
    pageModel: ListModel {
        ListElement {
            title: qsTr("Статистика")
            icon: "qrc:/qml/Statistics/images/statistics.png"
            page: "qrc:/qml/Statistics/StatisticsPage.qml"
        }
        ListElement {
            title: qsTr("Персонал")
            icon: "qrc:/qml/Personnel/images/personnel4.png"
    //            page: "Notifications/NotificationsPage.qml"
        }
        ListElement {
            title: qsTr("Безопасность полетов")
            icon: "qrc:/qml/Safety/images/safety8.png"
            page: "Safety/SafetyPage.qml"
        }
        ListElement {
            title: qsTr("Расписание")
            icon: "qrc:/qml/Shedule/images/shedule2.png"
            page: "Shedule/ShedulePage.qml"
        }
        ListElement {
            title: qsTr("Карты")
            icon: "qrc:/qml/Maps/images/maps.png"
    //            page: "Fitness/FitnessPage.qml"
        }
        ListElement {
            title: qsTr("Документы")
            icon: "qrc:/qml/Documents/images/documents.jpeg"
            //                page: "Fitness/FitnessPage.qml"
        }
        ListElement {
            title: qsTr("Настройки")
            icon: "qrc:/qml/Options/images/options.jpeg"
            //                page: "Fitness/FitnessPage.qml"
        }
    }
}
