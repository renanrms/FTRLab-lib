#include "FTRLab/Board.hpp"

void Board::connectToNetwork()
{
  String ssid, password;

  if (digitalRead(this->pins.networkButton) == LOW)
  {
    connectToNetworkSmartConfig();
    return;
  }

  if (this->preferences->isKey("ssid") && this->preferences->isKey("password"))
  {
    ssid = this->preferences->getString("ssid");
    password = this->preferences->getString("password");
  }

  if (!ssid.isEmpty())
  {
    Serial.print("Trying connection to " + ssid + " ");

    for (int attempts = 0; attempts < 3 && WiFi.status() != WL_CONNECTED; attempts++)
    {
      WiFi.begin(ssid.c_str(), password.c_str());
      WiFi.waitForConnectResult();
      Serial.print(".");
    }
    Serial.println("");

    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("Connection stablished. ");
      digitalWrite(this->pins.networkLed, HIGH);
    }
    else
    {
      Serial.println("Connection failed. Wifi status code: " + String(WiFi.status()));
    }
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    connectToNetworkSmartConfig();
  }
}
