#define BLYNK_TEMPLATE_ID "TMPL35voQYY6g"
#define BLYNK_TEMPLATE_NAME "SparkNerds"
#define BLYNK_AUTH_TOKEN "zz7aPw4uv-WnzhFUv7Oa1JglCERudHng"
#include <BlynkSimpleEsp32.h>
#include <Servo.h>
#include <NewPing.h>

#define TRIG_PIN 4
#define ECHO_PIN 2
#define MAX_DISTANCE 200

#define MOTOR_A_IN1 12
#define MOTOR_A_IN2 13
#define MOTOR_B_IN1 14
#define MOTOR_B_IN2 27
#define ENA 33
#define ENB 32

Servo myservo;
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

char auth[] = "zz7aPw4uv-WnzhFUv7Oa1JglCERudHng"; // Blynk Auth Token
char ssid[] = "rc"; // WiFi SSID
char pass[] = "123456789"; // WiFi Password

void setup() {
  Serial.begin(115200);
  
  // Initialize motor driver pins
  pinMode(MOTOR_A_IN1, OUTPUT);
  pinMode(MOTOR_A_IN2, OUTPUT);
  pinMode(MOTOR_B_IN1, OUTPUT);
  pinMode(MOTOR_B_IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Initialize Servo
  myservo.attach(15); 
  myservo.write(90); // Set servo to middle position

  // Initialize Blynk
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
  avoidObstacle();
}

void avoidObstacle() {
  int distance = sonar.ping_cm();
  
  if (distance > 0 && distance < 20) { // If obstacle detected within 20 cm
    stopCar(); // Stop the car
    delay(500);
    myservo.write(0); // Look left
    delay(500);
    
    int distanceLeft = sonar.ping_cm();
    
    myservo.write(180); // Look right
    delay(500);
    
    int distanceRight = sonar.ping_cm();
    
    myservo.write(90); // Reset to middle
    
    if (distanceLeft > distanceRight) {
      turnLeft();
    } else {
      turnRight();
    }
  } else {
    moveForward();
  }
}

void moveForward() {
  digitalWrite(MOTOR_A_IN1, HIGH);
  digitalWrite(MOTOR_A_IN2, LOW);
  digitalWrite(MOTOR_B_IN1, HIGH);
  digitalWrite(MOTOR_B_IN2, LOW);
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

void stopCar() {
  digitalWrite(MOTOR_A_IN1, LOW);
  digitalWrite(MOTOR_A_IN2, LOW);
  digitalWrite(MOTOR_B_IN1, LOW);
  digitalWrite(MOTOR_B_IN2, LOW);
}

void turnLeft() {
  digitalWrite(MOTOR_A_IN1, LOW);
  digitalWrite(MOTOR_A_IN2, HIGH);
  digitalWrite(MOTOR_B_IN1, HIGH);
  digitalWrite(MOTOR_B_IN2, LOW);
  delay(500);
}

void turnRight() {
  digitalWrite(MOTOR_A_IN1, HIGH);
  digitalWrite(MOTOR_A_IN2, LOW);
  digitalWrite(MOTOR_B_IN1, LOW);
  digitalWrite(MOTOR_B_IN2, HIGH);
  delay(500);
}
