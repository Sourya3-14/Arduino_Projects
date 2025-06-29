//Viral Science www.viralsciencecreativity.com www.youtube.com/c/viralscience
//Arduino NRF24L01 Transmitter - Joystick Controller Test
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h> //https://github.com/tmrh20/RF24/
#include <Wire.h>

#define joybtn1 1  // Joystick1 button 
#define joybtn2 0  // Joystick2 button 
#define tgl1 9   // Toggle switch 1
#define tgl2 6   // Toggle switch 1
#define btn1 2   // Button 1
#define btn2 3   // Button 2
#define btn3 4   // Button 3
#define btn4 5   // Button 4

RF24 radio(7, 8);   // nRF24L01 (CE, CSN)
const byte address[6] = "00001"; // Address

// Max size of this struct is 32 bytes - NRF24L01 buffer limit
struct Data_Package {
  byte joy1_X;
  byte joy1_Y;
  byte j1Button;
  byte joy2_X;
  byte joy2_Y;
  byte j2Button;
  byte pot1;
  byte pot2;
  byte tSwitch1;
  byte tSwitch2;
  byte button1;
  byte button2;
  byte button3;
  byte button4;

};
Data_Package data; //Create a variable with the above structure

void setup() {
  Serial.begin(9600);

  // radio communication
  radio.begin();
  radio.openWritingPipe(address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  
  pinMode(joybtn1, INPUT_PULLUP);
  pinMode(joybtn2, INPUT_PULLUP);
  pinMode(tgl1, INPUT_PULLUP);
  pinMode(tgl2, INPUT_PULLUP);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  pinMode(btn4, INPUT_PULLUP);
  
  // initial default values
  data.joy1_X = 127;
  data.joy1_Y = 127;
  data.joy2_X = 127;
  data.joy2_Y = 127;
  data.pot1 = 0;
  data.pot2 = 0;
  data.j1Button = 1;
  data.j2Button = 1;
  data.tSwitch1 = 1;
  data.tSwitch2 = 1;
  data.button1 = 1;
  data.button2 = 1;
  data.button3 = 1;
  data.button4 = 1;
}


void loop() {
  
  // Read all analog inputs and map them to one Byte value
  data.joy1_X = map(analogRead(A0), 0, 1023, 0, 255); // Convert the analog read value from 0 to 1023 into a BYTE value from 0 to 255
  data.joy1_Y = map(analogRead(A1), 0, 1023, 255, 0);
  data.joy2_X = map(analogRead(A2), 0, 1023, 0, 255);
  data.joy2_Y = map(analogRead(A3), 0, 1023, 0, 255);
  data.pot1 = map(analogRead(A6), 0, 1023, 0, 255);
  data.pot2 = map(analogRead(A7), 0, 1023, 0, 255);
  // data.joy1_X = analogRead(A0); // Convert the analog read value from 0 to 1023 into a BYTE value from 0 to 255
  // data.joy1_Y = map(analogRead(A1), 0, 1023, 1023, 0);
  // data.joy2_X = analogRead(A2);
  // data.joy2_Y = analogRead(A3);
  // data.pot1 = analogRead(A6);
  // data.pot2 = analogRead(A7);
  // Read all digital inputs
  data.j1Button = digitalRead(joybtn1);
  data.j2Button = digitalRead(joybtn2);
  data.tSwitch2 = digitalRead(tgl2);
  data.tSwitch1 = digitalRead(tgl1);
  data.button1 = digitalRead(btn1);
  data.button2 = digitalRead(btn2);
  data.button3 = digitalRead(btn3);
  data.button4 = digitalRead(btn4);
  
  radio.write(&data, sizeof(Data_Package)); // Send the whole data from the structure to the receiver
  delay(10);
}
