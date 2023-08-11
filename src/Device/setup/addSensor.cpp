#include "FTRLab/Device.hpp"

void Device::addSensor(Sensor *sensor)
{
  this->sensors.push_back(sensor);
}
