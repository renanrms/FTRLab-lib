#include "FTRLab/Device.hpp"

void Device::measurementTask()
{
  Serial.println("Measurement task running on core " + String(xPortGetCoreID()));

  while (true)
  {
    int64_t lastTime = NTP.micros();
    int64_t remainingTime = 0;
    while (this->client.connected())
    {
      lastTime = NTP.micros();

      this->takeAllMeasurements();

      remainingTime = this->targetTakeingPeriod - (NTP.micros() - lastTime);
      if (remainingTime > 0)
        delayMicroseconds(remainingTime);
    }
    delay(100);
  }
}
