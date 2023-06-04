#include "FTRLab.hpp"

class HallEffectSensor : public Sensor
{
public:
  HallEffectSensor()
  {
    this->name = "Efeito Hall";
    this->quantity = "magnetic_flux";
  }

  String takeMeasure()
  {
    String measure = String(hallRead());
    return measure;
  }
};
