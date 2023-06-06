#include "FTRLab/Board.hpp"

void Board::takeMeasurement(Sensor *sensor, unsigned index)
{
  float t1, t2, timestamp;

  t1 = this->getTimeFloat();
  String measure = sensor->takeMeasure();
  t2 = this->getTimeFloat();

  timestamp = (t1 + t2) / 2;

  this->measurements.push({index, timestamp, measure});
}
