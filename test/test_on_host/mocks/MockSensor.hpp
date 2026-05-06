#ifndef FTRLAB_MOCK_SENSOR_H
#define FTRLAB_MOCK_SENSOR_H

#include "FTRLab/Sensor.hpp"
#include <stdexcept>

class MockSensor : public Sensor
{
public:
  String returnValue = "42.0";
  int callCount = 0;
  bool shouldThrow = false;

  MockSensor() { quantity = "mock_quantity"; }

  String takeMeasure() override
  {
    callCount++;
    if (shouldThrow) throw std::runtime_error("sensor error");
    return returnValue;
  }
};

#endif
