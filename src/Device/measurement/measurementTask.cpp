#include "FTRLab/Device.hpp"

void Device::measurementTask()
{
  Serial.println("Measurement task running on core " + String(xPortGetCoreID()));

  while (true)
  {
    int64_t lastTime = NTP.millis();
    int64_t remainingTime = 0;
    while (this->client.connected())
    {
      lastTime = NTP.millis();

      this->takeAllMeasurements();

      remainingTime = this->targetTakeingPeriod - (NTP.millis() - lastTime);
      if (remainingTime > 0)
        delay(remainingTime);
    }
    delay(100);
  }
}
