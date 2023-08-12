#include "FTRLab/Device.hpp"

void Device::doSmartConfig()
{
  WiFi.mode(WIFI_AP_STA);
  WiFi.beginSmartConfig();

  Serial.print("Waiting for SmartConfig ");
  while (!WiFi.smartConfigDone())
  {
    digitalWrite(this->pins.networkLed, LOW);
    delay(500);
    digitalWrite(this->pins.networkLed, HIGH);
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("Connection established. ");
  digitalWrite(this->pins.networkLed, HIGH);

  this->preferences->putString("ssid", WiFi.SSID());
  this->preferences->putString("password", WiFi.psk());
}
