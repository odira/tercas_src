import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    visible: true
    width: 640; height: 640

    StackView {
        anchors.fill: parent
        initialItem: ListPage { }
    }
}
