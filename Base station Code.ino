#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
int text;
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

unsigned long lastReceiveTime = 0;
unsigned long currentTime = 0;

struct Data_Pakage{
  byte Data1;
  byte Data2;
  byte Data3;
};
Data_Pakage Data;


void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  resetData();
  
}

void loop() {
 
  if (radio.available()) {
    radio.read(&Data, sizeof(Data_Pakage));
    lastReceiveTime = millis();
  }currentTime = millis();

   if ( currentTime - lastReceiveTime > 1000 ) { 
    resetData(); 
  }
    //Serial.print("Roll: ");
    Serial.print(Data.Data1-93);
    Serial.print("/");
    //Serial.print("Pitch: ");
    Serial.print(Data.Data2-89);
    Serial.print("/");
    //Serial.print("Yaw: ");
    Serial.println(Data.Data3);

  }
  void resetData() {
    Data.Data1=90;
    Data.Data2=90;
    Data.Data3=90;
}
