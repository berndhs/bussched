import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import com.berndhs 1.0

Window {
    id: bigBox;
    visible: true
    width: 600;
    height: 400;

    function update() {
        console.log ("try to update")
        theSource.setXY(mapRect.x, mapRect.width, mapRect.y, mapRect.height);
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
//            theCanvas.paintShit();
            console.log ("found ",theSource.busPositions.rowCount(),"rows");
        }
    }
    Timer {
        id: refreshData;
        interval: 2*60*1000;
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
        color: "lightgrey"
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


//    Canvas {
//        id: theCanvas;
//        width: bigBox.width - 10;
//        height: bigBox.height - printButton.height;
//        anchors {
//            top: printButton.bottom;
//            left: bigBox.left;
//            leftMargin: 5;
//        }
//        onWidthChanged: {
//            theSource.setXY(x,x+width,y,y+height);
//        }
//        onHeightChanged: {
//            theSource.setXY(x,x+width,y,y+height);
//        }
//        Component.onCompleted: {
//            theSource.setXY(x,x+width,y,y+height);
//        }

//        function drawCircle (midX,midY, wid, hite) {

//            var context = getContext("2d");
//            context.beginPath();
//            context.fillStyle = "orange"
//            context.strokeStyle = "red"
//            context.moveTo(midX/2+60, midX/2);
//            context.arc(wid, hite/2, 60, 0, 2*Math.PI, true)
//            context.fill();
//            context.stroke();
//        }

//        function drawLine (context, fromx, fromy, tox, toy, color) {

//            context.beginPath();
//            context.lineWidth = 2;
//            context.moveTo(fromx, fromy);
//            context.strokeStyle = color;
//            context.lineTo(tox, toy);
//            context.stroke();
//        }

//        function drawCross (context, centerX, centerY, legLen, color) {
//            try {
//                var ctxx = getContext("2D");
//                console.log ("trying to draw cross ",ctxx,centerX,centerY,legLen,color)
//                ctxx.beginPath();
//                ctxx.lineWidth = 1;
//                ctxx.strokeStyle = color;
//                ctxx.moveTo(centerX-legLen,centerY);
//                ctxx.lineTo(centerX+legLen,centerY);
//                ctxx.moveTo(centerX,centerY-legLen);
//                ctxx.lineTo(centerX,centerY+legLen);
//                ctxx.stroke();
//                ctxx.fill();
//            } catch (err) {
//                console.log ("drawCross has an error", err)
//            }
//        }

//        function paintShit() {

//            // Get drawing context
//            var context = getContext("2d");

//            // Make canvas all white
//            context.beginPath();
//            context.clearRect(0, 0, width, height);
//            context.fill();

//            // Fill inside with blue, leaving 10 pixel border
//            context.beginPath();
//            context.fillStyle = "lightgrey"
//            context.fillRect(10, 10, width - 20, height - 20);
//            context.fill();

//            // Draw a line
//            context.beginPath();
//            context.lineWidth = 2;
//            context.moveTo(30, 30);
//            context.strokeStyle = "red"
//            context.lineTo(width-30, height-30);
//            context.stroke();

//            // another line
//            drawLine(context, 50, height/2, width/2, height/2, "blue")

//            // Draw a circle/*
//            context.beginPath();
//            context.fillStyle = "orange"
//            context.strokeStyle = "red"
//            context.moveTo(width/2+60, height/2);
//            context.arc(width/2, height/2, 60, 0, 2*Math.PI, true)
//            context.fill();
//            context.stroke();

//            // Draw some text
//            context.beginPath();
//            context.strokeStyle = "lime green"
//            context.font = "20px sans-serif";
//            context.text("Hello, world!", width/2, 50);
//            context.stroke();

//            // Draw some buses
////            var i;
////            var xxx = 287; var yyy = 235;
////            i=0;
////            var nrows = buses.rowCount();
////            while (i<nrows) {
////                drawLine(context,50,0,200,400,"green");
////                drawCross(context,Math.round(152),Math.round(145),5,"green")

////                drawCross(context,Math.round(xxx),Math.round(yyy),5,"blue")
////                drawCross(context,Math.round(xxx-50),Math.round(yyy+50),5,"blue")
////                var xx = buses.xPos(i);
////                var route = buses.route(i);
////                var lat = buses.lat(i);
////                var bear = buses.bearing(i);
////                var trip = buses.trip(i);
////                var lon = buses.lon(i);
////                var yy = buses.yPos(i);
////                drawCross(context,Math.round(xx),Math.round(yy),10,"red");
////                xxx= xx; yyy = yy;
////                if (i>0) break;

//////                console.log ("Bus Position ",i, " x " ,xx , " y " , yy , " rt " , route
//////                             , " lat/lon" , lat , lon , " bear " , bear , " trip " , trip);
////                ++i;
////            }

//            context.fill();
//        }

//        onPaint: {
//            paintShit();
//        }
//    }

}

