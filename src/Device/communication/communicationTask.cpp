#include "FTRLab/Device.hpp"
#include "FTRLab/internals/forceMdnsUpdateWrapper.hpp"

void Device::communicationTask()
{
  Serial.println("Communication task running on core " + String(xPortGetCoreID()));

  while (true)
  {
    if (WiFi.status() != WL_CONNECTED)
    {
      digitalWrite(this->pins.networkLed, LOW);
      this->connectToWifi();
      digitalWrite(this->pins.networkLed, HIGH);

      this->printNetworkInfo();
      this->setupNTP();
      this->server.begin();
      this->setupMdns();
    }

    while (WiFi.status() == WL_CONNECTED && !this->client.connected())
    {
      this->client = this->server.available(); // Disponibiliza o servidor para o cliente se conectar.
      delay(200);
    }

    if (this->client.connected())
    {
      Serial.println("Connection established to client " + this->client.remoteIP().toString() + ":" + String(this->client.remotePort()));
      // this->client.setNoDelay(true);
      this->mdnsUpdateTimer.detach();
      // this->forceMdnsUpdate();
      // delay(1000);
    }

    while (WiFi.status() == WL_CONNECTED && this->client.connected())
    {
      int64_t lastTime = NTP.millis();

      unsigned long measurementsSent = this->sendMeasurements();

      int64_t sendingTime = (NTP.millis() - lastTime);
      int64_t remainingTime = this->targetSendingPeriod - sendingTime;

      Serial.println("Sent " + String(measurementsSent) + " measurements in " + String(this->targetSendingPeriod - remainingTime) + " ms");

      if (remainingTime > 0)
        delay(remainingTime);
    }

    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("Connection to client ended.");
    }

    if (!this->mdnsUpdateTimer.active())
    {
      this->mdnsUpdateTimer.attach_ms(MDNS_FORCED_UPDATE_INTERVAL, &forceMdnsUpdateWrapper);
      // this->forceMdnsUpdate();
    }
  }
}
