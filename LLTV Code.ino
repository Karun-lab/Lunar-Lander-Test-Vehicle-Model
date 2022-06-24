#include <MPU6050.h>
#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "I2Cdev.h"
Servo s1;
Servo s2;

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

#define OUTPUT_READABLE_ACCELGYRO

struct Data_Pakage{
  byte Data1;
  byte Data2;
  byte Data3;
};
Data_Pakage Data;
int s1Pin=2;
int s2Pin=5;

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

int16_t ax, ay,az;
int16_t gx, gy,gz;
int x,y;
int smoothx, prex;
int smoothy, prey;
int smoothz, prez;
MPU6050 Tip;

void setup() {
  
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif
    
  Serial.begin(9600);
  Tip.initialize();
  s1.attach(s1Pin);
  s2.attach(s2Pin);
  s1.write(90);
  s2.write(90);
  delay(2500);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();


}

void loop() {
 Tip.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
 
 smoothx= (ax *0.07) +(prex * 0.93);
 smoothy= (ay *0.07) +(prey * 0.93);
 smoothz= (az *0.07) +(prez * 0.93);
 
 prex=smoothx;
 prey=smoothy;
 prez=smoothz;
 
Serial.print(smoothx); Serial.print("\t");Serial.println(smoothy);
  smoothx = map (smoothx , -17000, 17000, 180, 0);
  smoothy = map (smoothy , -17000, 17000, 180, 0); 
  smoothz = map (smoothz , -17000, 17000, 180, 0);      
     

  
  s1.write(smoothx);
  s2.write(smoothy);
  Data.Data1 = smoothx;
  Data.Data2 = smoothy;
  Data.Data3 = smoothz;

  radio.write(&Data, sizeof(Data_Pakage));

}
