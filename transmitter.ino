#include <ESP8266WiFi.h>
 
const char *ssid = "Redmi Note 9";
const char *password = "12345678";
const char *receiverIP = "192.168.94.180";
const int receiverPort = 80;  // Use any desired port
 
WiFiClient client;
int distance = 0;
 
// Sonar (Ultrasonic Sensor) configuration
const int trigPin = 4;  // GPIO pin connected to the trig pin of the sonar module
const int echoPin = 0;  // GPIO pin connected to the echo pin of the sonar module
 
void setup() {
  Serial.begin(115200);
 
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
 
  // Set up sonar pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
 
  // Set up transmitter
  Serial.println("Transmitter ready");
}
 
void loop() {
  // Read distance from sonar
  distance = getSonarDistance();
 
  // Determine value to send based on distance
  String valueToSend;
  if (distance > 20) {
    valueToSend = "11";
  } else if (distance > 10 && distance <= 20) {
    valueToSend = "10";
  } else {
    valueToSend = "00";
  }
  Serial.println(distance);
  // Send value to receiver
  if (client.connect(receiverIP, receiverPort)) {
    Serial.println("Connected to receiver");
    client.print("Value: ");
    client.println(valueToSend);
    client.stop();
  } else {
    Serial.println("Connection to receiver failed");
  }
 
  delay(100);  // Send every 5 seconds, adjust as needed
}
 
int getSonarDistance() {
  // Trigger sonar to send pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the duration of the echo pulse
  unsigned long duration = pulseIn(echoPin, HIGH);
 
  // Convert duration to distance (in cm) using the speed of sound
  int distance = duration * 0.034 / 2;
 
  return distance;
}
