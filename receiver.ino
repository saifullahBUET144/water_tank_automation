#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
 
const char *ssid = "Redmi Note 9";
const char *password = "12345678";
const int receiverPort = 80;
 
WiFiServer server(receiverPort);
int count = 0;
 
void setup() {
  Serial.begin(115200);
 
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
 
  // Set up receiver
  server.begin();
  Serial.println("Receiver ready");
}
 
void loop() {
  WiFiClient client = server.available();
 
  if (client) {
    Serial.println("New client connected");
    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r');
        Serial.println(request);
        // Extract count number from the received message
        int pos = request.indexOf("Count: ");
        if (pos != -1) {
          count = request.substring(pos + 7).toInt();
          Serial.print("Received Count: ");
          Serial.println(count);
        }
 
        client.flush();
      }
    }
    //client.stop();
    //Serial.println("Client disconnected");
  }
}
