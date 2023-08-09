#include "FTRLab/Board.hpp"

void Board::sendMeasurements()
{
  if (!this->measurements.empty())
    this->sendMeasurementsBatch();

  while (!this->measurements.empty() &&
         (this->measurements.front().timestamp - NTP.micros() / 1000000.0 > 0.5))
  {
    delay(50);
    this->sendMeasurementsBatch();
  }
}
