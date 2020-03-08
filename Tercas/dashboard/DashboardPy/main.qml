import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    id: rootWindow
    title: qsTr("TERCAS Dashboard - Основное Окно")
    visible: true
    visibility: {
        if (Qt.platform.os === "linux")
            return "FullScreen";
        else if (Qt.platform.os === "osx")
            return "FullScreen";
//            return "Maximized";
    }

    background: Rectangle {
        color: "lightblue"
    }

    StackView {
        id: stackView

        anchors.fill: parent
        focus: true
        initialItem: MainPage { }
    }
}
