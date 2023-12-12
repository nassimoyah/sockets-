#include <Arduino.h>

#include <WiFi.h>

char* ssid = "esp32"; 
char* pass = "123456789i"; 

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, pass);
  Serial.println("establishing connecting to " + String(ssid)); 

while (WiFi.status() != WL_CONNECTED){
  delay(1000);
  Serial.println(".");
}

Serial.println("connected to wifi " + String(ssid));
Serial.println(WiFi.localIP());

}

void loop() {
  
}

output : 

connected to wifi esp32
192.168.43.250

