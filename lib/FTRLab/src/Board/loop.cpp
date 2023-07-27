#include "FTRLab/Board.hpp"

void Board::loop()
{
  int64_t lastTakingTime = NTP.micros();
  int64_t lastSendingTime = NTP.micros();

  if (WiFi.status() == WL_CONNECTED)
  {
    digitalWrite(this->pins.networkLed, HIGH);
  }
  else
  {
    digitalWrite(this->pins.networkLed, LOW);
    board.setup();
  }

  this->tcp();

  if (this->client.connected())
  {
    while (lastTakingTime - lastSendingTime < this->measurementSendingPeriod)
    {
      int64_t remainingTime = this->minimumMeasurementPeriod - (NTP.micros() - lastTakingTime);
      delayMicroseconds(remainingTime > 0 ? remainingTime : 0);
      this->takeAllMeasurements();
      lastTakingTime = NTP.micros();
    }
    this->sendMeasurements();
    lastSendingTime = NTP.micros();
  }
  else
  {
    delay(100);
  }
}
