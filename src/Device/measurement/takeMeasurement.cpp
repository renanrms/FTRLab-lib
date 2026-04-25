#include "FTRLab/Device.hpp"

void Device::takeMeasurement(Sensor *sensor, unsigned index)
{
  int64_t t1, t2;
  double timestamp;

  try
  {
    t1 = this->timeProvider->micros();
    String measure = sensor->takeMeasure();
    t2 = this->timeProvider->micros();

    timestamp = ((double)(t1 + t2) / 2) / 1000000.0;

    while (xSemaphoreTake(this->measurementsSemaphore, portMAX_DELAY) != pdTRUE)
    {
      delay(10);
    }
    this->measurements.push({index, timestamp, measure});
    xSemaphoreGive(this->measurementsSemaphore);
  }
  catch (std::exception error)
  {
    Serial.println("Measurement error from sensor " + String((unsigned int)index) + ".");
  }
}
