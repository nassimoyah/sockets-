#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

char* ssid = "esp32"; 
char* pass = "123456789i";

WebServer server(80);

String webpage1 ="<!DOCTYPE html><html><head><title>Page Title</title></head><body style='background-color: #EEEEEE;'><span style='color: #003366;'><h1>This is a Heading</h1><p>the random number is :" ;
String webpage2 = "</p></span></body></html>";
String webpage = webpage1 + String(random(100)) + webpage2;

int interval = 1000;
unsigned long prev = 0; 

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

server.on("/", []() {
  server.send(200, "text/html", webpage);
});
server.begin();
}

void loop() {
  server.handleClient();
  unsigned long now = millis(); 
  if( now-prev > 1000 ){
     webpage = webpage1 + String(random(100)) + webpage2;
    prev = now;
  }
}

