#include "FTR-Lab.hpp"

void Board::takeAllMeasurements()
{
  for (unsigned index = 0; index < this->sensors.size(); index++)
  {
    this->takeMeasurement(this->sensors[index], index);
  }
}
