import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

ScrollView {
    id: root
//    width: view.width
//    height: view.height
//    Layout.fillWidth: true
//    Layout.fillHeight: true
//        anchors.fill: view
//        anchors.margins: 10
//    width: 800
//    height: 300
    ScrollBar.vertical.policy: ScrollBar.AlwaysOn

    ColumnLayout {
//        Layout.preferredWidth: parent.width

        Layout.fillWidth: true
//        width: 500
        Layout.fillHeight: true
//        anchors.fill: parent

        TextField {
            Layout.fillWidth: true
            text: surname
        }
        TextField { text: model.name }
        TextField { text: middlename }
        TextField { text: birthday }
        TextField { text: mobile_phone }
        TextField { text: tab_num }
        TextField { text: position }
        TextField { text: model.class }
        TextField { text: shift_num }
        TextField { text: sectors_pool }
        TextField { text: service_period }
        TextField { text: admission }
        TextField { text: note }
    }
}
