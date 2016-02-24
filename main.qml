import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import com.berndhs 1.0

Window {
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
        text: qsTr("Hello World " + theSource.reqCount)
        anchors.centerIn: parent
    }

    Button {
        id: printButton;
        anchors {
            horizontalCenter: helloText.horizontalCenter;
            top: helloText.bottom;
            topMargin: 20;
        }
        text: "Print";
        onClicked: {
            theSource.printData();
        }
    }
}
