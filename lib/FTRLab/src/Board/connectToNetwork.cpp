#include "FTRLab/Board.hpp"

void Board::connectToNetwork()
{
  WiFi.mode(WIFI_AP_STA);
  WiFi.beginSmartConfig();
  // Wifi.softAP();
  Serial.print("Waiting for SmartConfig ");
  while (!WiFi.smartConfigDone())
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("SmartConfig received.");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
}
