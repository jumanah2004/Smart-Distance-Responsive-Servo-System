# 📡 Smart-Distance-Responsive-Servo-System

---

## 💡 Project Idea

The core concept is to build an environmental response system that mimics automated decision-making. The ultrasonic sensor emits high-frequency sound waves that bounce off nearby objects. By calculating the travel time of the echo pulse, the Arduino determines the precise distance in centimeters.

Based on predefined distance ranges, the system executes distinct motor positions:
- **Close Distance(>=10):** Servo rotates to **180**.
- **Medium Distance (>=25):** Servo rotates to **90**.
- **Far Distance (>=25):** Servo resets to its default position at **180**.

---

## 🛠️ Components Used

* **Microcontroller:** Arduino UNO (or compatible board)
* **Distance Sensor:** Ultrasonic Sensor (HC-SR04)
* **Actuator:** Micro Servo Motor (TowerPro SG90)
* **Connectors:** Jumper Wires (Male-to-Male / Male-to-Female)
* **Prototyping / Mounting:** Breadboard or Cardboard Chassis
* **Power/Data:** USB Type-A to Type-B Cable

---

## 🔌 Circuit Diagram

![Circuit Diagram](https://github.com/jumanah2004/Smart-Distance-Responsive-Servo-System/blob/d72dcc598bcde0e1505eff5c01365c2c18551378/imeg1.jpeg)  
---

### Pinout Connections:
- **HC-SR04 Ultrasonic Sensor:**
  - `VCC` ⬅️ Arduino `5V`
  - `GND` ⬅️ Arduino `GND`
  - `Trig` ⬅️ Pin `11`
  - `Echo` ⬅️ Pin `12`
- **SG90 Servo Motor:**
  - **Brown/Black Cable (GND):** ⬅️ Arduino `GND`
  - **Red Cable (VCC):** ⬅️ Arduino `5V`
  - **Yellow/Orange Cable (Signal):** ⬅️ Pin `9`

---

## 💻 Source Code & Explanation

```cpp
#include <Servo.h> // Include the Servo library

Servo servo; // Create a servo object to control the motor

// Define pins for the ultrasonic sensor
int trigPin = 11;
int echoPin = 12;

// Variables to store pulse duration and calculated distance
long duration;
int distance;

void setup()
{
  // Attach the servo object to digital pin 9
  servo.attach(9);
  servo.write(0); // Initialize servo position to 0 degrees
  delay(2000);

  // Set pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop()
{
  // 1. Send a 10-microsecond HIGH pulse to trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // 2. Read the duration of the return pulse on the Echo pin
  duration = pulseIn(echoPin, HIGH);

  // 3. Calculate distance in cm (Speed of sound = 0.034 cm/us)
  distance = duration * 0.034 / 2;

  // Print calculated distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // ==========================================
  // 🔄 Modified Conditional Logic
  // ==========================================
  // Multi-threshold logic driving distinct actuation levels
  if (distance <= 10)
  {
    servo.write(90);  // Level 1: Close proximity -> rotate to 90 degrees
  }
  else if (distance <= 25)
  {
    servo.write(180); // Level 2: Medium proximity -> rotate to 180 degrees
  }
  else
  {
    servo.write(0);   // Level 3: No target detected -> return to 0 degrees
  }

  delay(200); // Short delay to stabilize sensor readings
}
