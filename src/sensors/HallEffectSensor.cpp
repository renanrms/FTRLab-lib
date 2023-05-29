#include "FTR-Lab.hpp"

class HallEffectSensor : public Sensor
{
  const char *name = "Efeito Hall";
  const char *quantity = "magnetic_flux";

  String takeMeasure()
  {
    String measure = String(hallRead());
    return measure;
  }
};
