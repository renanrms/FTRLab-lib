#include "FTRLab/Board.hpp"

void Board::takeMeasurement(Sensor *sensor, unsigned index)
{
  time_t t1, t2, timestamp;

  time(&t1);
  String measure = sensor->takeMeasure();
  time(&t2);

  timestamp = (t1 + t2) / 2;

  this->measurements.push({index, timestamp, measure});
}
