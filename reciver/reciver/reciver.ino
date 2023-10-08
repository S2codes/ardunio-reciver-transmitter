#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

int IN1 = 3;
int IN2 = 2;
int IN3 = 4;
int IN4 = 5;

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
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(9600);


  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
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

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("STOP");
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Go FORWARD");
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Go BACKWARD");
}


void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Turn LEFT");
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Turn RIGHT");
}




void loop() {
  while (radio.available()) {

    // Serial.println("Reciving data ...\n");

    radio.read(&data, sizeof(data));

    // digitalWrite(led01, data.toggleSwitch01);
    // digitalWrite(led02, data.toggleSwitch02);

    LeftX = map(data.joystickLeft_x, 0, 1023, 0, 180);
    LeftY = map(data.joystickLeft_y, 0, 1023, 0, 180);

    // Right Joystick
    RightX = map(data.joystickRight_x, 0, 1023, 0, 180);
    RightY = map(data.joystickRight_y, 0, 1023, 0, 180);

    // if (LeftY < 95 && LeftY > 89) {
    if ((LeftY < 95 && LeftY > 89) && (RightY < 95 && RightY > 89)) {
      stopMotors();
    }
    if (LeftY > 95) {
      moveForward();
    }
    if (LeftY < 89) {
      moveBackward();
    }

    if (RightX < 89) {
      turnLeft();
    }
    if (RightX > 95) {
      turnRight();
    }


    Serial.print("LX :");
    Serial.print(" :");
    Serial.print(LeftX);
    Serial.print("  LY :");
    Serial.print(" :");
    Serial.print(LeftY);

    
    Serial.print(" RX :");
    Serial.print(RightX);
    Serial.print(" RY :");
    Serial.print(RightY);
    Serial.print("\n");

    // esc_signal.writeMicroseconds(RightY);
  }
}