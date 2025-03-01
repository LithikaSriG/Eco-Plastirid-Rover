// Motor control pins
int motor1 = 8;
int motor2 = 9;
int motor3 = 10;
int motor4 = 11;
void setup() {
  // Motor pins setup
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);

  Serial.begin(9600); // Initialize Serial monitor for debugging (optional)
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();
    // Execute motor control based on received command
    switch (command) {
      case 'F': // Move forward
        moveForward();
        break;
      case 'B': // Move backward
        moveBackward();
        break;
      case 'L': // Turn left
        turnLeft();
        break;
      case 'R': // Turn right
        turnRight();
        break;
      case 'S': // Stop
        stopMotors();
        break;
      default:
        // Handle unrecognized commands or errors
        break;
    }
  }
}

void moveForward() {
  // Right motor forward
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);

  // Left motor forward
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, LOW);
}

void moveBackward() {
  // Right motor backward
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, HIGH);

  // Left motor backward
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, HIGH);
}

void turnLeft() {
  // Right motor forward
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);

  // Left motor backward
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, HIGH);
}

void turnRight() {
  // Right motor backward
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, HIGH);

  // Left motor forward
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, LOW);
}

void stopMotors() {
  // Stop all motors
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, LOW);
}
