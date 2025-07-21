#define m1 7  // Right Motor MA1
#define m2 8  // Right Motor MA2
#define m3 9  // Left Motor MB1
#define m4 10  // Left Motor MB2
#define e1 6  // Right Motor Enable Pin EA
#define e2 5 // Left Motor Enable Pin EB

//**********4 Channel IR Sensor Connection**********//
#define irL A1   // Left Sensor
#define irM1 A2  // Middle Left Sensor
#define irM2 A3  // Middle Right Sensor
#define irR A4  // Right Sensor
//*************************************************//

void setup() {
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  pinMode(e1, OUTPUT);
  pinMode(e2, OUTPUT);
  pinMode(irL, INPUT);
  pinMode(irM1, INPUT);
  pinMode(irM2, INPUT);
  pinMode(irR, INPUT);
}

void loop() {
  // Reading Sensor Values
  int sL = digitalRead(irL);   // Left Sensor
  int sM1 = digitalRead(irM1); // Middle Left Sensor
  int sM2 = digitalRead(irM2); // Middle Right Sensor
  int sR = digitalRead(irR);   // Right Sensor

  // Convert readings for clarity: 0 = black line detected
  bool middleDetected = (sM1 == 0 || sM2 == 0);

  // Move Forward (line in the middle)
  if (sL == 1 && sM1 == 0 && sM2 == 0 && sR == 1) {
    moveForward(120);
  }
  // Slight Right (left middle detects line)
  else if (sL == 1 && sM1 == 0 && sM2 == 1 && sR == 1) {
    turnRight(120);
  }
  // Slight Left (right middle detects line)
  else if (sL == 1 && sM1 == 1 && sM2 == 0 && sR == 1) {
    turnLeft(120);
  }
  // Sharp Right (left sensor detects line)
  else if (sL == 0 && middleDetected == false && sR == 1) {
    turnRight(80);
  }
  // Sharp Left (right sensor detects line)
  else if (sL == 1 && middleDetected == false && sR == 0) {
    turnLeft(80);
  }
  // All sensors detect black (e.g., junction or stop)
  else if (sL == 0 && sM1 == 0 && sM2 == 0 && sR == 0) {
    stopMotors();
  }
  // Line lost (no sensor detects line) - stop or search
  else if (sL == 1 && sM1 == 1 && sM2 == 1 && sR == 1) {
    stopMotors(); // You can change to search behavior
  }
  else {
    // Default fallback
    moveForward(120);
  }
}

//========= Motor Control Functions ==========//
void moveForward(int speed) {
  analogWrite(e1, speed);
  analogWrite(e2, speed);
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  digitalWrite(m3, HIGH);
  digitalWrite(m4, LOW);
}

void turnRight(int speed) {
  analogWrite(e1, speed);
  analogWrite(e2, speed);
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, LOW);
}

void turnLeft(int speed) {
  analogWrite(e1, speed);
  analogWrite(e2, speed);
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m3, HIGH);
  digitalWrite(m4, LOW);
}

void stopMotors() {
  digitalWrite(m1, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, LOW);
}
