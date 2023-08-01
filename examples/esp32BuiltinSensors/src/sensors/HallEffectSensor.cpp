#include "FTRLab.hpp"

class HallEffectSensor : public Sensor
{
public:
  HallEffectSensor()
  {
    this->quantity = "magnetic_flux";
    this->method = "Efeito Hall";
  }

  String takeMeasure()
  {
    int measure = hallRead();
    return String(measure);
  }
};
