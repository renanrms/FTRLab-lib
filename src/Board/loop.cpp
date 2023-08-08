#include "FTRLab/Board.hpp"

void Board::loop()
{
  int64_t lastTakingTime = NTP.micros();
  int64_t remainingTime;

  while (true)
  {
    if (this->client.connected())
    {
      remainingTime = this->minimumMeasurementPeriod - (NTP.micros() - lastTakingTime);
      Serial.println("Measurement remainingTime = " + String(remainingTime));
      if (remainingTime > 0)
      {
        delayMicroseconds(remainingTime);
      }
      lastTakingTime = NTP.micros();
      this->takeAllMeasurements();
    }
    else
    {
      delay(100);
    }
  }
}
