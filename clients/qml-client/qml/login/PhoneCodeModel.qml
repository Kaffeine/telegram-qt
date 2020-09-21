import QtQml.Models 2.3

ListModel {
    ListElement {
        code: "44"
        country: qsTr("United Kingdom")
        length: 10
    }
    ListElement {
        code: "7"
        country: qsTr("Russian Federation")
        length: 10
    }
    ListElement {
        code: "34"
        country: qsTr("Spain")
        length: 9 // 6 or 7, followed by 8 digits
    }
    ListElement {
        code: "49"
        country: qsTr("Germany")
        length: 11
    }
    ListElement {
        code: ""
        country: "Custom"
        length: 15
    }
}
