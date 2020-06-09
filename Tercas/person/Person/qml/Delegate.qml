import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Package {

    Item {
        id: listDelegate
        Package.name: 'list'
        width: parent.width; height: 50

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true

            TextField { text: surname }
            TextField { text: name }
            TextField { text: middlename }
            TextField { text: birthday }
            TextField { text: mobile_phone }
            TextField { text: tab_num }
            TextField { text: position }
            TextField { text: 'class' }
            TextField { text: shift_num }
            TextField { text: sectors_pool }
            TextField { text: admission }
            TextField { text: note }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: console.log(listView.currentIndex)
        }
    }

    Item {
        id: singleDelegate
        Package.name: 'single'
        width: root.width; height: root.height
    }
}
