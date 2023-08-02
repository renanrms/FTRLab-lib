#include "FTRLab.hpp"

#ifdef __cplusplus
extern "C"
{
#endif
  // cspell:disable-next-line
  uint8_t temprature_sens_read();

#ifdef __cplusplus
}
#endif

// cspell:disable-next-line
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
    // cspell:disable-next-line
    float measure = (temprature_sens_read() - 32) / 1.8;
    return String(measure);
  }
};
