#include "FTRLab/Device.hpp"
#include "FTRLab/internals/SemaphoreLock.hpp"

void Device::takeMeasurement(Sensor *sensor, unsigned index)
{
  int64_t t1, t2;
  double timestamp;

  try
  {
    t1 = NTP.micros();
    String measure = sensor->takeMeasure();
    t2 = NTP.micros();

    timestamp = ((double)(t1 + t2) / 2) / 1000000.0;

    SemaphoreLock lock = SemaphoreLock(this->measurementsSemaphore);
    this->measurements.push({index, timestamp, measure});
    lock.~SemaphoreLock();
  }
  catch (std::exception error)
  {
    Serial.println("Measurement error from sensor " + String(index) + ".");
  }
}
