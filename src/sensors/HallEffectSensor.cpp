#include "FTR-Lab.hpp"

class HallEffectSensor : public Sensor
{
public:
  HallEffectSensor()
  {
    this->name = String("Efeito Hall");
    this->quantity = String("magnetic_flux");
  }

  String takeMeasure()
  {
    String measure = String(hallRead());
    return measure;
  }
};
