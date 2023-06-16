#include "FTRLab/Board.hpp"

void Board::takeMeasurement(Sensor *sensor, unsigned index)
{
  int64_t t1, t2;
  double timestamp;

  try
  {
    t1 = NTP.micros();
    String measure = sensor->takeMeasure();
    t2 = NTP.micros();

    timestamp = ((double)(t1 + t2) / 2) / 1000000.0;

    this->measurements.push({index, timestamp, measure});
  }
  catch (std::exception error)
  {
    Serial.println("Measurement error from sensor " + String(index) + ".");
  }
}
