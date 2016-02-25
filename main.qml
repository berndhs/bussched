import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import com.berndhs 1.0

Window {
    id: bigBox;
    visible: true
    width: 600;
    height: 400;

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
            theCanvas.paintShit();
            console.log ("found ",theSource.busPositions.rowCount(),"rows");
        }
    }

//    ListModel {
//        id: imgData;
//        ListElement {
//            the_x: 100;
//            the_y: 100;
//            label: "1"
//        }
//        ListElement {
//            the_x: 50;
//            the_y: 100;
//            label: "2"
//        }
//        ListElement {
//            the_x: 200;
//            the_y: 400;
//            label: "3"
//        }
//        ListElement {
//            the_x: 500;
//            the_y: 500;
//            label: "4"
//        }
//        ListElement {
//            the_x: 510;
//            the_y: 510;
//            label: "5"
//        }
//        ListElement {
//            the_x: 510;
//            the_y: 510;
//            label: "6"
//        }
//    }


    Canvas {
        id: theCanvas;
        width: bigBox.width - 10;
        height: bigBox.height - printButton.height;
        anchors {
            top: printButton.bottom;
            left: bigBox.left;
            leftMargin: 5;
        }
        onWidthChanged: {
            theSource.setXY(x,x+width,y,y+height);
        }
        onHeightChanged: {
            theSource.setXY(x,x+width,y,y+height);
        }
        Component.onCompleted: {
            theSource.setXY(x,x+width,y,y+height);
        }

        function drawCircle (midX,midY, wid, hite) {

            var context = getContext("2d");
            context.beginPath();
            context.fillStyle = "orange"
            context.strokeStyle = "red"
            context.moveTo(midX/2+60, midX/2);
            context.arc(wid, hite/2, 60, 0, 2*Math.PI, true)
            context.fill();
            context.stroke();
        }

        function paintShit() {

            // Get drawing context
            var context = getContext("2d");

            // Make canvas all white
            context.beginPath();
            context.clearRect(0, 0, width, height);
            context.fill();

            // Fill inside with blue, leaving 10 pixel border
            context.beginPath();
            context.fillStyle = "lightgrey"
            context.fillRect(10, 10, width - 20, height - 20);
            context.fill();

            // Draw a line
            context.beginPath();
            context.lineWidth = 2;
            context.moveTo(30, 30);
            context.strokeStyle = "red"
            context.lineTo(width-30, height-30);
            context.stroke();

            // Draw a circle
            drawCircle(width/2,height/2,width/2,height/2)/*
            context.beginPath();
            context.fillStyle = "orange"
            context.strokeStyle = "red"
            context.moveTo(width/2+60, height/2);
            context.arc(width/2, height/2, 60, 0, 2*Math.PI, true)
            context.fill();
            context.stroke();*/

            // Draw some text
            context.beginPath();
            context.strokeStyle = "lime green"
            context.font = "20px sans-serif";
            context.text("Hello, world!", width/2, 50);
            context.stroke();

            // Draw some buses
            context.beginPath();
            context.fillStyle = "orange"
            context.strokeStyle = "red"
            var i;
            for (i=0; i<buses.rowCount(); i++) {
                var xx = buses.xPos(i);
                var route = buses.route(i);
                var lat = buses.lat(i);
                var bear = buses.bearing(i);
                var trip = buses.trip(i);
                var lon = buses.lon(i);
                var yy = buses.yPos(i);
                drawCircle(xx,yy,5,5);

                console.log ("Bus Position ",i, " x " ,xx , " y " , yy , " rt " , route
                             , " lat/lon" , lat , lon , " bear " , bear , " trip " , trip);
            }

            context.fill();
        }

        onPaint: {
            paintShit();
        }
    }


//    Rectangle {
//        id: drawingMap;
//        width: bigBox.width - 10;
//        height: bigBox.height - printButton.height;
//        anchors.left: parent.left;
//        anchors.leftMargin: 5;
//        anchors.top: printButton.bottom;
//        z: 20;
//        property real basex: x;
//        property real basey: y;
//        color: "lightgrey";
//        clip: true;
//        ListView {
//            anchors.fill: drawingMap
//            width: drawingMap.width;
//            height: drawingMap.height;
//            model: imgData;
//            z: 25;
//            delegate: Image {
//                id: busIcon;
//                x: the_x + drawingMap.basex;
//                y: the_y + drawingMap.basey;
//                z: 50;
//                source: "file:///home/bernd/mywork/publictransit/bussched/images/smallbus.jpg"
//                clip: true;
//                Text {
//                    x: the_x + drawingMap.basex;
//                    y: the_y + drawingMap.basey;
//                    z: 100;
//                    text: label;
//                    color: "red";
//                    font.pixelSize: 8;
//                }
//            }
//        }
//    }
}

