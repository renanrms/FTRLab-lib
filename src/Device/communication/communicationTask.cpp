#include "FTRLab/Device.hpp"

void Device::communicationTask()
{
  Serial.println("Communication task running on core " + String(xPortGetCoreID()));

  while (true)
  {
    if (!this->networkProvider->isConnected())
    {
      this->gpioProvider->digitalWrite(this->pins.networkLed, LOW);
      this->connectToWifi();
      this->gpioProvider->digitalWrite(this->pins.networkLed, HIGH);

      this->printNetworkInfo();
      this->setupNTP();
      this->networkProvider->serverBegin();
      this->setupMdns();
    }

    while (this->networkProvider->isConnected() && !this->networkProvider->clientConnected())
    {
      this->networkProvider->acceptClient();
      delay(200);
    }

    if (this->networkProvider->clientConnected())
    {
      Serial.println("Connection established to client " +
                     this->networkProvider->clientRemoteIP() + ":" +
                     String(this->networkProvider->clientRemotePort()));

      this->forceMdnsUpdate();
      delay(1000);
      this->tickerProvider->detach();
      this->discoveryServiceProvider->end();
    }

    while (this->networkProvider->isConnected() && this->networkProvider->clientConnected())
    {
      int64_t lastTime = this->timeProvider->micros();

      unsigned long measurementsSent = this->sendMeasurements();

      int64_t sendingTime = (this->timeProvider->micros() - lastTime);
      int64_t remainingTime = this->targetSendingPeriod - sendingTime;

      Serial.println("Sent " + String((unsigned long)measurementsSent) + " measurements in " +
                     String((double)(this->targetSendingPeriod - remainingTime) / 1000.0, 3) + " ms");

      if (remainingTime > 0)
        delayMicroseconds(remainingTime);
    }

    if (this->networkProvider->isConnected())
    {
      Serial.println("Connection to client ended.");
      this->setupMdns();
    }
  }
}
