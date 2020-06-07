import QtQuick 2.12

Package {

    Text {
        id: listDelegate
        Package.name: 'list'
        width: parent.width; height: 50
        text: surname + ' ' + name
    }

    Text {
        id: singleDelegate
        Package.name: 'single'
        width: root.width; height: root.height
        text: surname + ' ' + name + ' ' + middlename
    }
}
