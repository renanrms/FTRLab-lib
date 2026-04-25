#include "FTRLab/Device.hpp"

void Device::measurementTask()
{
  Serial.println("Measurement task running on core " + String(xPortGetCoreID()));

  while (true)
  {
    while (this->networkProvider->clientConnected())
    {
      int64_t lastTime = this->timeProvider->micros();

      this->takeAllMeasurements();

      int64_t remainingTime = this->targetTakingPeriod - (this->timeProvider->micros() - lastTime);
      if (remainingTime > 0)
        delayMicroseconds(remainingTime);
    }
    delay(100);
  }
}
