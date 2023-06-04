#include "FTRLab.hpp"

class HallEffectSensor : public Sensor
{
  const String name = String("Efeito Hall");
  const String quantity = String("magnetic_flux");

  String takeMeasure()
  {
    String measure = String(hallRead());
    return measure;
  }
};
