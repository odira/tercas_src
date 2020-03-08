import QtQuick 2.7
import QtLocation 5.6
import QtPositioning 5.5

Map {
    id: map

    plugin: Plugin {
        id: plugin
        name: "osm"
    }
    center {
        latitude: -55.0
        longitude: 33.0
    }
    zoomLevel: 5
    gesture.enabled: true
}


//PositionSource {
//     id: positionSource
// }

// Map {
//     id: map
//     property MapCircle circle

//     Component.onCompleted: {
//         circle = Qt.createQmlObject('import QtLocation 5.3; MapCircle {}', page)
//         circle.center = positionSource.position.coordinate
//         circle.radius = 5000.0
//         circle.color = 'green'
//         circle.border.width = 3
//         map.addMapItem(circle)
//     }
// }
