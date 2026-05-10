#include <ESP32Servo.h>
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
int wet = 0;
// create four servo objects
Servo shoulder;
Servo base;
Servo gripper;
Servo elbow;

// Published values for SG90 servos; adjust if needed
int minUs = 1000;
int maxUs = 2000;

// These are all GPIO pins on the ESP32
// Recommended pins include 2,4,12-19,21-23,25-27,32-33
int uart1[] = { 19, 18 };  //(Tx,Rx) HC12
int shoulderPin = 32;
int basePin = 33;
int gripperPin = 16;
int elbowpin = 17;

int elbow_min = 0;
int elbow_max = 180;
int elbow_pos = 0;

int gripper_min = 0;
int gripper_max = 180;
int gripper_pos = 0;

int shoulder_min = 0;
int shoulder_max = 180;
int shoulder_pos = 0;

int base_min = 15;
int base_max = 180;
int base_pos = 15;

int IN[] = { 25, 26, 27, 13 };

int pos = 0;  // position in degrees
long previostime = 0;
long currenttime = 0;
int timeout = 20;
ESP32PWM pwm;
void setup() {
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  Serial.begin(9600);
  Serial1.begin(9600, SERIAL_8N1, uart1[1], uart1[0]);
  Serial1.setTimeout(50);
  shoulder.setPeriodHertz(50);  // Standard 50hz servo
  base.setPeriodHertz(50);      // Standard 50hz servo
  gripper.setPeriodHertz(50);   // Standard 50hz servo
  elbow.setPeriodHertz(50);     // Standard 50hz servo
  SerialBT.begin("Arm Robot");  // Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  shoulder.attach(shoulderPin, minUs, maxUs);
  base.attach(basePin, minUs, maxUs);
  gripper.attach(gripperPin, minUs, maxUs);
  elbow.attach(elbowpin, minUs, maxUs);
  pinMode(IN[0], OUTPUT);
  pinMode(IN[1], OUTPUT);
  pinMode(IN[2], OUTPUT);
  pinMode(IN[3], OUTPUT);
  digitalWrite(IN[0], LOW);
  digitalWrite(IN[1], LOW);
  digitalWrite(IN[2], LOW);
  digitalWrite(IN[3], LOW);
}

void loop() {
  if (Serial1.available() > 0) {
    // Read the incoming data as a string
    String receivedData = Serial1.readStringUntil('\n');

    // Print the received data to the primary serial for debugging
    // Serial.println("Received: " + receivedData);

    // Parse the received data (comma-separated values)
    parseData(receivedData, base_pos, shoulder_pos, elbow_pos);

    // Print parsed values for debugging
    Serial.print("Base: ");
    Serial.print(base_pos);
    Serial.print(" Shoulder: ");
    Serial.print(shoulder_pos);
    Serial.print(" Elbow: ");
    Serial.println(elbow_pos);

    // Add your logic here to control the robot arm or other actions
  }
  if (SerialBT.available()) {
    char rx = SerialBT.read();
    if (rx == 'S') {
      Serial.println("STOP");
      rover_control("0000");
    } else if (rx == 'R') {
      Serial.println("Forward");
      rover_control("1000");
    } else if (rx == 'Q') {
      Serial.println("Bacward");
      rover_control("0100");
    } else if (rx == 'O') {
      Serial.println("LEFT");
      rover_control("0010");
    } else if (rx == 'P') {
      Serial.println("Right");
      rover_control("0001");
    } else if (rx == 'C') {
      Serial.println("Shoulder UP");
      shoulder_pos++;
    } else if (rx == 'D') {
      Serial.println("Shoulder Down");
      shoulder_pos--;
    } else if (rx == 'F') {
      Serial.println("Elbow UP");
      elbow_pos--;
    } else if (rx == 'E') {
      Serial.println("Elbow Down");
      elbow_pos++;
    } else if (rx == 'G') {
      Serial.println("Gripper UP");
      gripper_pos++;
      Serial.println(gripper_pos);
    } else if (rx == 'H') {
      Serial.println("Gripper Down");
      gripper_pos--;
      Serial.println(gripper_pos);
    } else if (rx == 'B') {
      Serial.println("base Clockwise");
      base_pos++;
    } else if (rx == 'A') {
      Serial.println("base Counter Clockwise");
      base_pos--;
    }
  }
  if (elbow_pos > elbow_max) {
    elbow_pos = elbow_max;
  } else if (elbow_pos < elbow_min) {
    elbow_pos = elbow_min;
  }

  if (shoulder_pos > shoulder_max) {
    shoulder_pos = shoulder_max;
  } else if (shoulder_pos < shoulder_min) {
    shoulder_pos = shoulder_min;
  }

  if (gripper_pos > gripper_max) {
    gripper_pos = gripper_max;
  } else if (gripper_pos < gripper_min) {
    gripper_pos = gripper_min;
  }
  if (base_pos > base_max) {
    base_pos = base_max;
  } else if (base_pos < base_min) {
    base_pos = base_min;
  }

  elbow.write(elbow_pos);
  shoulder.write(shoulder_pos);
  base.write(base_pos);
  gripper.write(gripper_pos);
}

void rover_control(String buttonstat) {
  if (buttonstat[0] == '1') {
    digitalWrite(IN[0], HIGH);
    digitalWrite(IN[1], LOW);
    digitalWrite(IN[2], HIGH);
    digitalWrite(IN[3], LOW);
  } else if (buttonstat[1] == '1') {
    digitalWrite(IN[0], LOW);
    digitalWrite(IN[1], HIGH);
    digitalWrite(IN[2], LOW);
    digitalWrite(IN[3], HIGH);
  } else if (buttonstat[2] == '1') {
    digitalWrite(IN[0], LOW);
    digitalWrite(IN[1], HIGH);
    digitalWrite(IN[2], HIGH);
    digitalWrite(IN[3], LOW);
  } else if (buttonstat[3] == '1') {
    digitalWrite(IN[0], HIGH);
    digitalWrite(IN[1], LOW);
    digitalWrite(IN[2], LOW);
    digitalWrite(IN[3], HIGH);
  } else {
    digitalWrite(IN[0], LOW);
    digitalWrite(IN[1], LOW);
    digitalWrite(IN[2], LOW);
    digitalWrite(IN[3], LOW);
  }
}
// Function to parse comma - separated data into individual integers
void parseData(String data, int &pitch, int &roll, int &yaw) {
  int index1 = data.indexOf(',');              // Find the first comma
  int index2 = data.indexOf(',', index1 + 1);  // Find the second comma

  // Extract substrings and convert to integers
  pitch = data.substring(0, index1).toInt();
  roll = data.substring(index1 + 1, index2).toInt();
  yaw = data.substring(index2 + 1).toInt();
}