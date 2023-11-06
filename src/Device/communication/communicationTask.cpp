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

      this->forceMdnsUpdate();
      delay(1000);
      this->mdnsUpdateTimer.detach();
      MDNS.end();
    }

    while (WiFi.status() == WL_CONNECTED && this->client.connected())
    {
      int64_t lastTime = NTP.micros();

      unsigned long measurementsSent = this->sendMeasurements();

      int64_t sendingTime = (NTP.micros() - lastTime);
      int64_t remainingTime = this->targetSendingPeriod - sendingTime;

      Serial.println("Sent " + String(measurementsSent) + " measurements in " + String((this->targetSendingPeriod - remainingTime) / 1000.0, 3) + " ms");

      if (remainingTime > 0)
        delayMicroseconds(remainingTime);
    }

    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("Connection to client ended.");
      this->setupMdns();
    }
  }
}
