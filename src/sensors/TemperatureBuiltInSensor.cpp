#include "FTRLab.hpp"

#ifdef __cplusplus
extern "C"
{
#endif

  uint8_t temprature_sens_read();

#ifdef __cplusplus
}
#endif

uint8_t temprature_sens_read();

class TemperatureBuiltInSensor : public Sensor
{
public:
  TemperatureBuiltInSensor()
  {
    this->quantity = "temperature";
    this->method = "Temperatura da CPU";
  }

  String takeMeasure()
  {
    float measure = (temprature_sens_read() - 32) / 1.8;
    return String(measure);
  }
};
