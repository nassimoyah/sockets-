#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include<WebSocketsServer.h>

WebSocketsServer websocket(81); // standard port for web socket 81 ( websoket is an instance )

char* ssid = "esp32"; 
char* pass = "123456789i";

WebServer server(80);

String website = "<!DOCTYPE html><html><head><title>Page Title</title></head><body style='background-color: #EEEEEE;'><span style='color: #003366;'><h1>Lets generate a random number</h1><p>The random number is: <span id='rand'>-</span></p><p><button type='button' id='BTN_SEND_BACK'>Send info to ESP32</button></p></span></body><script> var Socket; document.getElementById('BTN_SEND_BACK').addEventListener('click', button_send_back); function init() { Socket = new WebSocket('ws://' + window.location.hostname + ':81/'); Socket.onmessage = function(event) { processCommand(event); }; } function button_send_back() { Socket.send('Sending back some random stuff'); } function processCommand(event) { document.getElementById('rand').innerHTML = event.data; console.log(event.data); } window.onload = function(event) { init(); }</script></html>";

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
  server.send(200, "text/html", website);
});
server.begin();
websocket.begin();
}

void loop() {
  websocket.loop();
  server.handleClient();
  unsigned long now = millis(); 
  if( now-prev > 1000 ){
    String str = String(random(100));                 // create a random value
    int str_len = str.length() + 1;                   
    char char_array[str_len];
    str.toCharArray(char_array, str_len); 
    websocket.broadcastTXT(char_array, str_len); 
    prev = now;
  }
}

