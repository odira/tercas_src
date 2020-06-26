import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Package {

    DelegateList {
        id: listDelegate
        Package.name: 'list'
        width: listView.width
        height: 50
    }

    DelegateSingle {
        id: singleDelegate
        Package.name: 'single'
        width: singleView.width
        height: singleView.height
        anchors.margins: 5
    }

}
