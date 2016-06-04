#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <vector>

WiFiUDP port;

const int serverPort = 55123;
IPAddress serverIP(192, 168, 1, 3);

void WiFiSetup() {
  WiFi.begin("", "");
  port.begin(9999);

}

void sendMessage(const std::vector<float> &data) {
  OSCMessage msg("/data");
  for (int i=0; i<data.size(); i++) {
    msg.add(data[i]);
    Serial.print(i);
    Serial.print(": ");
    Serial.println(data[i]);
  }

  port.beginPacket(serverIP,serverPort);
  msg.send(port);
  port.endPacket();
  
  msg.empty(); // free space occupied by message
}

