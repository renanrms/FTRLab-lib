#include "FTRLab/Board.hpp"

void Board::connectToNetworkSmartConfig()
{
  WiFi.mode(WIFI_AP_STA);
  WiFi.beginSmartConfig();

  Serial.print("Waiting for SmartConfig ");
  while (!WiFi.smartConfigDone())
  {
    digitalWrite(18, HIGH);
    delay(500);
    digitalWrite(18, LOW);
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("SmartConfig received.");

  this->preferences->putString("ssid", WiFi.SSID());
  this->preferences->putString("password", WiFi.psk());
}
