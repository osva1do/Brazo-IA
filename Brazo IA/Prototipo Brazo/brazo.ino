#include <Servo.h>

const int pin = 13;
int incomingByte;

Servo servoBase, servoCodo, servoAnte, servoM, gripper;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servoBase.attach(5);
  servoCodo.attach(6);
  servoAnte.attach(8);
  servoM.attach(9);
  gripper.attach(10);
  pinMode(pin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();

    switch (incomingByte) {
      case 'T':
        clasifyTriangle();
        break;
      case 'R':
        clasifySquare();
        break;
      case 'C':
        clasifyCircle();
        break;
      case 'D':
        noMovement();
    }
  } else {
    noMovement();
  }
}

void noMovement() {
  servoBase.write(120);
  servoCodo.write(90);
  servoAnte.write(120);
  servoM.write(90);
  gripper.write(0);
}

void clasifyTriangle() {
  servoBase.write(120);
  delay(400);
  servoCodo.write(30);
  delay(400);
  servoAnte.write(85);
  delay(400);
  servoM.write(90);
  delay(400);
  gripper.write(180);
  delay(400);
  gripper.write(0);  //PARA EL TAMANO DEL OBJETO
  delay(500);
  servoCodo.write(85);
  delay(300);
  servoM.write(70);
  delay(300);
  servoBase.write(0);  // DONDE QUEDA LA FIGURA
  delay(600);
  servoM.write(60);
  delay(300);
  servoAnte.write(180);
  delay(300);
  gripper.write(180);
  delay(500);
  noMovement();
}

void clasifySquare() {
  servoBase.write(120);
  delay(400);
  servoCodo.write(30);
  delay(400);
  servoAnte.write(85);
  delay(400);
  servoM.write(90);
  delay(400);
  gripper.write(180);
  delay(400);
  gripper.write(0);  // <--------
  delay(500);
  servoCodo.write(85);
  delay(300);
  servoM.write(70);
  delay(300);
  servoBase.write(50);  // <-------
  delay(600);
  servoM.write(60);
  delay(300);
  servoAnte.write(180);
  delay(300);
  gripper.write(180);
  delay(500);
  noMovement();
}

void clasifyCircle() {
  servoBase.write(120);
  delay(400);
  servoCodo.write(30);
  delay(400);
  servoAnte.write(85);
  delay(400);
  servoM.write(90);
  delay(400);
  gripper.write(180);
  delay(400);
  gripper.write(0);  // <--------
  delay(500);
  servoCodo.write(85);
  delay(300);
  servoM.write(70);
  delay(300);
  servoBase.write(30);  // <---------
  delay(600);
  servoM.write(60);
  delay(300);
  servoAnte.write(180);
  delay(300);
  gripper.write(180);
  delay(500);
  noMovement();
}