import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import com.berndhs 1.0

Window {
    id: bigBox;
    visible: true
    width: 800;
    height: 600;

    function update() {
        console.log ("try to update")
        theSource.updateMap();
        theSource.askPositions();
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
            bigBox.update();
            console.log ("found ",theSource.busPositions.rowCount(),"rows");
        }
    }
    Button {
        id: stopButton;
        anchors {
            left: printButton.right; leftMargin: 10;
            top: printButton.top;
        }
        text: "Stop";
        onClicked: {
            theSource.stop();
        }
    }

    Text {
        id: busCount;
        anchors {
            left: stopButton.right; leftMargin: 20;
            top: bigBox.top; topMargin: 5;
        }
        text: theSource.busCount + qsTr(" Buses");
    }

    Timer {
        id: refreshData;
        interval: 10 * 1000; // 2*60*1000;
        repeat: true;
        running: true;
        onTriggered: {
            console.log ("refreshData try update");
            bigBox.update();
        }
    }

    Connections {
        target: theSource;
        onNewMap: {
            busPos.imageFile = mapName;
        }
    }

    Rectangle {

        id: mapRect;
        width: bigBox.width;
        height: bigBox.height - printButton.height;
        color: "#f0ffff"
        anchors {
            top: printButton.bottom;
            left: bigBox.left;
            leftMargin: 5;
        }
        Image {
            id: busPos;
            anchors.fill: mapRect;
            property string imageFile: ""
            source: "file://" + imageFile;
            width: bigBox.width - 10;
            height: bigBox.height - printButton.height;
        }
    }

}

