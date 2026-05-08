#include "FTRLab/Device.hpp"

static void mdnsUpdateCallback(void *devicePtr)
{
  static_cast<Device *>(devicePtr)->forceMdnsUpdate();
}

void Device::setupMdns()
{
  if (!this->discoveryServiceProvider->begin(this->chipId.c_str()))
  {
    Serial.println("Error setting up mDNS responder!");
    while (true)
    {
      this->gpioProvider->digitalWrite(this->pins.networkLed, LOW);
      delay(1950);
      this->gpioProvider->digitalWrite(this->pins.networkLed, HIGH);
      delay(50);
    }
  }

  Serial.println("\n===== Adding mDNS service =====");
  Serial.println("Name: " + SERVICE_NAME);
  Serial.println("Protocol: " + PROTOCOL);
  Serial.println("Port: " + String(PORT));
  Serial.println();

  this->discoveryServiceProvider->addService(SERVICE_NAME.c_str(), PROTOCOL.c_str(), PORT);

  this->updateMdnsTxtData();

  this->tickerProvider->attach_ms(MDNS_FORCED_UPDATE_INTERVAL, mdnsUpdateCallback, this);
}
