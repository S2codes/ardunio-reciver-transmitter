#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <Servo.h>

// Servo esc_signal;

Servo S1;
Servo S2;
Servo S3;
Servo S4;

int velocity = 0;

int LeftX = 0;
int LeftY = 0;
int RightX = 0;
int RightY = 0;


RF24 radio(7, 8);
const byte address[] = "12345";

void setup() {
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.startListening();

  S1.attach(9);
  S2.attach(6);
  S3.attach(5);
  S4.attach(3);
  delay(2000);


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
  while (radio.available()) {

    // Serial.println("Reciving data ...\n");

    radio.read(&data, sizeof(data));

    // digitalWrite(led01, data.toggleSwitch01);
    // digitalWrite(led02, data.toggleSwitch02);

    LeftX = map(data.joystickLeft_x, 0, 1023, 180, 0);
    LeftY = map(data.joystickLeft_y, 0, 1023, 180, 0);
    
    Serial.print("LX :");
    Serial.print(data.joystickLeft_x);
    Serial.print(" :");
    Serial.print(LeftX);
    Serial.print("  LY :");
    Serial.print(data.joystickLeft_y);
    Serial.print(" :");
    Serial.print(LeftY);

    // Right Joystick
    RightX = map(data.joystickRight_x, 0, 1023, 180, 0);
    RightY = map(data.joystickRight_y, 0, 1023, 180, 0);

    
    Serial.print(" RX :");
    Serial.print(data.joystickRight_x);
    Serial.print(" RY :");
    Serial.print(data.joystickRight_y);
    Serial.print("\n");

    // esc_signal.writeMicroseconds(RightY);

    S1.write(RightX);
    S2.write(RightY);
    S3.write(LeftX);
    S4.write(LeftY);


  }
}