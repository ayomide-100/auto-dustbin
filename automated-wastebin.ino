// Define pins for the ultrasonic sensor, LED, and buzzer
const int trigPin = 3;
const int echoPin = 2;
const int ledPin = 7;
const int buzzerPin = 8;  // Buzzer connected to pin 8

// Variables to store distance and duration
long duration;
int distance;
unsigned long lastDetectionTime = 0;  // Store the last time an object was detected
bool objectDetected = false;          // To track if an object is currently detected

void setup() {
  pinMode(trigPin, OUTPUT);   // Set the trigger pin as output
  pinMode(echoPin, INPUT);    // Set the echo pin as input
  pinMode(ledPin, OUTPUT);    // Set the LED pin as output
  pinMode(buzzerPin, OUTPUT); // Set the buzzer pin as output
  Serial.begin(9600);         // Start the serial communication
}

void loop() {
  // Send a 10us pulse to trigger the sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo pin and calculate the distance
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;  // Convert to cm

  // If an object is within range (10 cm), turn on the LED and the buzzer, reset the timer
  if (distance <= 5) {
    digitalWrite(ledPin, HIGH);    // Turn on the LED
    tone(buzzerPin, 5000);         // Turn on the buzzer with a 1000Hz tone
    objectDetected = true;         // Mark object as detected
    lastDetectionTime = millis();  // Reset the timer
  } else {
    // If the object is out of range, check if the LED and buzzer should turn off after 3 seconds
    if (objectDetected && millis() - lastDetectionTime >= 500) {  // 3 seconds delay
      digitalWrite(ledPin, LOW);   // Turn off the LED
      noTone(buzzerPin);           // Turn off the buzzer
      objectDetected = false;      // Mark object as not detected
    }
  }

  // Print the distance for debugging
  Serial.print("Distance: ");
  Serial.println(distance);

  delay(200);  // Small delay for sensor stability
}