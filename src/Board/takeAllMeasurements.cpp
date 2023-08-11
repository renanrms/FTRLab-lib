#include "FTRLab/Device.hpp"

void Device::takeAllMeasurements()
{
  for (unsigned index = 0; index < this->sensors.size(); index++)
  {
    this->takeMeasurement(this->sensors[index], index);
  }
}
