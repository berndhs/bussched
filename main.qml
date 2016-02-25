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
            var ctx = theCanvas.getContext('2d');
            ctx.strokeStyle = Qt.rgba(0, 0, 0, 1);
            theCanvas.loadImage(theCanvas.imgurl);
            ctx.drawImage(theCanvas.imgurl,50,50);
            ctx.stroke();
            console.log("have image ",theCanvas.gotImage)
        }
    }

    Canvas {
        id: theCanvas;
        width: bigBox.width;
        height: bigBox.height;
        anchors.top: printButton.bottom;
        anchors.left: bigBox.left;
        property bool gotImage: false;
        property string imgurl: "file:///home/bernd/mywork/publictransit/bussched/images/smallbus.jpg"
        Component.onCompleted: {
            loadImage(imgurl)
        }

        onImageLoaded: {
            gotImage = true;
        }
    }
}
