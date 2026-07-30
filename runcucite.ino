#include <Servo.h>

Servo servo;

int trigPin = 11;
int echoPin = 12;

// Variables
long duration;
int distance;

void setup()
{
  servo.attach(9);
  servo.write(0);
  delay(2000);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
}

void loop()
{
  // إرسال نبضة للحساس
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // قراءة زمن النبضة
  duration = pulseIn(echoPin, HIGH);

  // حساب المسافة بالسنتيمتر
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // التحكم بالسيرفو
  if (distance <= 10)
  {
    servo.write(180);
  }
  else
  {
    servo.write(0);
  }

  delay(200);
}