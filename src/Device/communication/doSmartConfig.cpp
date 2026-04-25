#include "FTRLab/Device.hpp"

void Device::doSmartConfig()
{
  this->networkProvider->mode(WIFI_AP_STA);
  this->networkProvider->beginSmartConfig();

  Serial.print("Waiting for SmartConfig ");
  while (!this->networkProvider->smartConfigDone())
  {
    this->gpioProvider->digitalWrite(this->pins.networkLed, LOW);
    delay(500);
    this->gpioProvider->digitalWrite(this->pins.networkLed, HIGH);
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("Connection established. ");
  this->gpioProvider->digitalWrite(this->pins.networkLed, HIGH);

  this->keyValueStoreProvider->putString("ssid", this->networkProvider->SSID().c_str());
  this->keyValueStoreProvider->putString("password", this->networkProvider->psk().c_str());
}
