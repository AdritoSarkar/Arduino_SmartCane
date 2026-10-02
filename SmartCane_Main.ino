const int trigPin = 9;
const int echoPin = 10;
const int buzzer = 11;
const int ledPin = 13;

long duration;
int distance;
int lastDistance = 100;

unsigned long lastBeepTime = 0;

void setup() {
  // Initialize digital/analog pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Wait for echo
  duration = pulseIn(echoPin, HIGH, 30000);

  // Only update distance if we got a valid reading
  if (duration > 0) {
    distance = duration * 0.0343 / 2;

    // Only accept reasonable distances
    if (distance >= 2 && distance <= 400) {
      lastDistance = distance;
    }
  }

  // Use last valid measurement
  distance = lastDistance;

  Serial.print("Distance: ");
  Serial.println(distance);

  // -------------------------
  // BUZZER BEHAVIOR
  // -------------------------

  // Farther than 50 cm = completely silent
  if (distance > 50) {
    digitalWrite(buzzer, LOW);
    digitalWrite(ledPin, LOW);
  }

  // 31-50 cm = slow beeps
  else if (distance > 30) {
    digitalWrite(ledPin, HIGH);

    if (millis() - lastBeepTime >= 700) {
      digitalWrite(buzzer, HIGH);
      delay(80);
      digitalWrite(buzzer, LOW);
      lastBeepTime = millis();
    }
  }

  // 21-30 cm = medium beeps
  else if (distance > 20) {
    digitalWrite(ledPin, HIGH);

    if (millis() - lastBeepTime >= 450) {
      digitalWrite(buzzer, HIGH);
      delay(80);
      digitalWrite(buzzer, LOW);
      lastBeepTime = millis();
    }
  }

  // 11-20 cm = faster beeps
  else if (distance > 10) {
    digitalWrite(ledPin, HIGH);

    if (millis() - lastBeepTime >= 250) {
      digitalWrite(buzzer, HIGH);
      delay(80);
      digitalWrite(buzzer, LOW);
      lastBeepTime = millis();
    }
  }

  // 6-10 cm = very fast beeps
  else if (distance > 5) {
    digitalWrite(ledPin, HIGH);

    if (millis() - lastBeepTime >= 120) {
      digitalWrite(buzzer, HIGH);
      delay(60);
      digitalWrite(buzzer, LOW);
      lastBeepTime = millis();
    }
  }

  // 5 cm or closer = continuous beep
  else {
    digitalWrite(buzzer, HIGH);
    digitalWrite(ledPin, HIGH);
  }

  delay(60);
}