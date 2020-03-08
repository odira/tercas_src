import QtQuick 2.7

Rectangle {
    id: singleView

    width: 100
    height: 100
    color: "orange"
    opacity: 0.2

    property int currentIndex: -1
    onCurrentIndexChanged: {
        dateWid.date = safetyModel.get(currentIndex).datetime
        accText.text = safetyModel.get(currentIndex).acc
        departmentText.text = "Подразделение:" + "<i>" + safetyModel.get(currentIndex).department_id + "</i>"
        shiftText.text = "Смена " + safetyModel.get(currentIndex).shift
        sectorText.text = "Сектор: " + safetyModel.get(currentIndex).sector_id
        locationText.text = "Location:" + safetyModel.get(currentIndex).location
        classificationText.text = safetyModel.get(currentIndex).classification
        typeText.text = safetyModel.get(currentIndex).type
        terkasText.text = "СПОС Terkas:" + safetyModel.get(currentIndex).terkas
        alphaText.text = "СПОС Alpha:" + safetyModel.get(currentIndex).alpha
        tcas1Text.text = "TCAS 1:" + safetyModel.get(currentIndex).tcas1
        tcas2Text.text = "TCAS 2:" + safetyModel.get(currentIndex).tcas2
        causeText.text = safetyModel.get(currentIndex).cause
        factorText.text = safetyModel.get(currentIndex).factor
        detailsText.text = safetyModel.get(currentIndex).details
    }

    Column {
        id: contentColumn

        anchors.fill: parent
        anchors.margins: 10
        clip: true
        spacing: 5

        Date {
            id: dateWid
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Text {
            id: accText

            anchors.horizontalCenter: parent.horizontalCenter
            renderType: Text.NativeRendering
            font.pointSize: 16
            color: "#e07a2e"
        }
        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10

            Text {
                id: departmentText

                renderType: Text.NativeRendering
            }
            Text {
                id: shiftText

                renderType: Text.NativeRendering
            }
        }
        Text {
            id: sectorText

            anchors.horizontalCenter: parent.horizontalCenter
            renderType: Text.NativeRendering
        }
        Text {
            id: locationText
            anchors.horizontalCenter: parent.horizontalCenter
            renderType: Text.NativeRendering
        }
        Text {
            id: classificationText
            anchors.horizontalCenter: parent.horizontalCenter
            renderType: Text.NativeRendering
            wrapMode: Text.WordWrap
        }
        Text {
            id: typeText
            anchors.horizontalCenter: parent.horizontalCenter
            renderType: Text.NativeRendering
            wrapMode: Text.WordWrap
        }
        Text {
            id: terkasText
            anchors.horizontalCenter: parent.horizontalCenter
            renderType: Text.NativeRendering
        }
        Text {
            id: alphaText
            anchors.horizontalCenter: parent.horizontalCenter
            renderType: Text.NativeRendering
        }
        Text {
            id: tcas1Text
            anchors.horizontalCenter: parent.horizontalCenter
            renderType: Text.NativeRendering
        }
        Text {
            id: tcas2Text
            anchors.horizontalCenter: parent.horizontalCenter
            renderType: Text.NativeRendering
        }
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            font.bold: true
            font.pointSize: 10
            color: "orange"
            text: "Описание события"
        }
        Text {
            id: detailsText
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            renderType: Text.NativeRendering
        }
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            renderType: Text.NativeRendering
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            text: "Событие произошло в результате следующих факторов:"
        }
        Text {
            id: factorText

            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            visible: factorText.text.length > 0 ? true : false;
            renderType: Text.NativeRendering
        }
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            renderType: Text.NativeRendering
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            text: "Причины события:"
        }
        Text {
            id: causeText
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            renderType: Text.NativeRendering
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        }
    }
}

