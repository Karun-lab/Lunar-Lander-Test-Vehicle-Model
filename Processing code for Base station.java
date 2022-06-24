import processing.serial.*;
import java.awt.event.KeyEvent;
import java.io.IOException;
Serial myPort;
float roll, pitch,yaw;
String data="";

void setup() {
  size (960, 640, P3D);
  myPort = new Serial(this, "COM12", 9600); // starts the serial communication
  myPort.bufferUntil('\n');
}


void draw() {
  translate(width/2, height/2, 0);
  background(33);
  textSize(22);
  text("Roll: " + int(roll) + "     Pitch: " + int(pitch), -100, 265);

  // Rotate the object
  rotateX(radians(roll));
  rotateZ(radians(-pitch));

  
  // 3D 0bject
    
  box (386, 40, 200); // Draw box
    
  //2nd cube
  
  translate(0,-37);
  box(346, 35, 150);
  
  //cylinders
  translate(170,57,80);
  drawCylinder(20,20,150,24);
  //2cyl
  translate(-340,0,0);
  drawCylinder(20,20,150,24);
  //3cyl
  translate(0,0,-160);
  drawCylinder(20,20,150,24);
  //4cyl
  translate(340,0,0);
  drawCylinder(20,20,150,24);

  }
  
  void drawCylinder(float topRadius, float bottomRadius, float tall, int sides) {
    float angle = 0;
    float angleIncrement = TWO_PI / sides;
    beginShape(QUAD_STRIP);
    for (int i = 0; i < sides + 1; ++i) {
        vertex(topRadius*cos(angle), 0, topRadius*sin(angle));
        vertex(bottomRadius*cos(angle), tall, bottomRadius*sin(angle));
        angle += angleIncrement;
    }
    endShape();
  }
  
  // Read data from the Serial Port
void serialEvent (Serial myPort) { 
  // reads the data from the Serial Port up to the character '.' and puts it into the String variable "data".
  data = myPort.readStringUntil('\n');
  // if you got any bytes other than the linefeed:
  if (data != null) {
    data = trim(data);
    // split the string at "/"
    String items[] = split(data, '/');
    if (items.length > 1) {
      //--- Roll,Pitch in degrees
      roll = float(items[0]);
      pitch = float(items[1]);
   
    }
  }
}
