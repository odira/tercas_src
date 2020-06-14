import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

ScrollView {
    anchors.fill: parent

    ColumnLayout {
        anchors.fill: parent

        TextField {
            Layout.preferredWidth: 500
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
