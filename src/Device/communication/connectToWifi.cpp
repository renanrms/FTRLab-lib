#include "FTRLab/Device.hpp"

void Device::connectToWifi()
{
  String ssid, password;

  if (this->gpioProvider->digitalRead(this->pins.networkButton) == LOW)
  {
    this->doSmartConfig();
    return;
  }

  if (this->keyValueStoreProvider->isKey("ssid") && this->keyValueStoreProvider->isKey("password"))
  {
    ssid = this->keyValueStoreProvider->getString("ssid");
    password = this->keyValueStoreProvider->getString("password");
  }

  if (!ssid.isEmpty())
  {
    Serial.print("\nTrying connection to " + ssid + " ");

    for (int attempts = 0; attempts < 3 && this->networkProvider->status() != WL_CONNECTED; attempts++)
    {
      this->networkProvider->begin(ssid.c_str(), password.c_str());
      this->networkProvider->waitForConnectResult();
      Serial.print(".");
    }
    Serial.println("");

    if (this->networkProvider->status() == WL_CONNECTED)
    {
      Serial.println("Connection established. ");
      this->gpioProvider->digitalWrite(this->pins.networkLed, HIGH);
    }
    else
    {
      Serial.println("Connection failed. Wifi status code: " + String(this->networkProvider->status()));
    }
  }

  if (this->networkProvider->status() != WL_CONNECTED)
  {
    this->doSmartConfig();
  }
}
