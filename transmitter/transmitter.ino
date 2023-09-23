#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

// declaring where the toggle switches are connected in Arduino
// int toggleSwitch01pin = 3;
// int toggleSwitch02pin = 4;

// declaring where the leftHandside joystick is connected
int joystickLeft_VRxPin = A1;
int joystickLeft_VRyPin = A0;

// declaring where the rightHandside joystick is connected
int joystickRight_VRxPin = A3;
int joystickRight_VRyPin = A2;

RF24 radio(7, 8);
const byte address[] = "12345";

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.stopListening();

  pinMode(joystickLeft_VRxPin, INPUT);
  pinMode(joystickLeft_VRyPin, INPUT);
  
  pinMode(joystickRight_VRxPin, INPUT);
  pinMode(joystickRight_VRyPin, INPUT);

  // pinMode(toggleSwitch01pin, INPUT);
  // pinMode(toggleSwitch02pin, INPUT);
  Serial.begin(9600);
}

struct datapack {
  // bool toggleSwitch01 ;
  // bool toggleSwitch02 ;

  int joystickLeft_x;
  int joystickLeft_y;

  int joystickRight_x;
  int joystickRight_y;
};
datapack data;

void loop() {
  // data.toggleSwitch01 = digitalRead(toggleSwitch01pin);
  // data.toggleSwitch02 = digitalRead(toggleSwitch02pin);

  // data.joystickLeft_x = map(analogRead(joystickLeft_VRxPin), 0, 1023,0,255);
  data.joystickLeft_x = analogRead(joystickLeft_VRxPin);
  // data.joystickLeft_y = map(analogRead(joystickLeft_VRyPin), 0, 1023,0,255);
  data.joystickLeft_y = analogRead(joystickLeft_VRyPin);

  Serial.print("LeftX : ");
  Serial.print(data.joystickLeft_x);
  Serial.print(" LeftY : ");
  Serial.print(data.joystickLeft_y);
  // Serial.print("\n \n ");

  // data.joystickRight_x = map(analogRead(joystickRight_VRxPin) , 520, 1023,0,255);
  data.joystickRight_x = analogRead(joystickRight_VRxPin);
  // data.joystickRight_y = map(analogRead(joystickRight_VRyPin) , 0, 1023,0,255);
  data.joystickRight_y = analogRead(joystickRight_VRyPin);

  Serial.print(" RightX : ");
  Serial.print(data.joystickRight_x);

  Serial.print(" RightY : ");
  Serial.print(data.joystickRight_y);
  Serial.print("\n");
  // Serial.print("\n \n");

  radio.write(&data, sizeof(data));
  // Serial.println("Send.............");
  // delay(1000);
}