import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Package {

    DelegateList {
        id: listDelegate
        Package.name: 'list'
        width: parent.width
        height: 60
    }

    DelegateSingle {
        id: singleDelegate
        Package.name: 'single'
//        Layout.preferredWidth: view.width
        width: view.width
        height: view.height
//        Layout.fillHeight: true
//        anchors.margins: 10
//        anchors.fill: view
    }

}
