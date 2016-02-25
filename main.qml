import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import com.berndhs 1.0

Window {
    id: bigBox;
    visible: true
    width: 600;
    height: 400;

    Source {
        id: theSource;
        Component.onCompleted: {
            askPositions();
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    Text {
        id: helloText;
        anchors {
            top: bigBox.top; topMargin: 5;
            left: bigBox.left; leftMargin: 5;
        }

        text: qsTr("Hello World " + theSource.reqCount)
    }

    Button {
        id: printButton;
        anchors {
            left: helloText.right; leftMargin: 10;
            top: bigBox.top;
        }
        text: "Paint";
        onClicked: {
        }
    }

    ListModel {
        id: imgData;
        ListElement {
            thex: 100;
            they: 100;
        }
        ListElement {
            thex: 50;
            they: 100;
        }
        ListElement {
            thex: 200;
            they: 50;
        }
    }



    Rectangle {
        id: drawingMap;
        width: bigBox.width - 10;
        height: bigBox.height - printButton.height;
        anchors.left: parent.left;
        anchors.leftMargin: 5;
        anchors.top: printButton.bottom;
        property real basex: x;
        property real basey: y;
        color: "lightgrey";
        ListView {
            anchors.fill: drawingMap
            model: imgData;
            delegate: Rectangle {
                color: "red";
                width: 3; height: 3; radius: height/2;
                x: thex + drawingMap.basex;
                y: they + drawingMap.basey;
                z: 50;
    //            Image {
    //                source: "/home/bernd/mywork/publictransit/bussched/images/smallbus.jpg";
    //                x: thex;
    //                y: they;
    //                z: 50;
    //            }
                Image {
                    anchors.centerIn: parent;
                    source: "file:///home/bernd/mywork/publictransit/bussched/images/smallbus.jpg"
                    clip: true;
                }
            }
        }
    }
}
