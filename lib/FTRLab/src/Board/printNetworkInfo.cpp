#include "FTRLab/Board.hpp"

void Board::printNetworkInfo()
{
  Serial.println("\n===== Network info =====");
  Serial.print("SSID: ");
  Serial.println(this->ssid);
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Subnet Mask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("Broadcast: ");
  Serial.println(WiFi.broadcastIP());
  Serial.print("DNS 1: ");
  Serial.println(WiFi.dnsIP(0));
  Serial.print("DNS 2: ");
  Serial.println(WiFi.dnsIP(1));
}
