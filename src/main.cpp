#include "FTRLab.hpp"

#include "sensors/HallEffectSensor.cpp"

Preferences ftrlabPreferences;

void setup()
{
  ftrlabPreferences.begin("FRTLab", false);
  board.setName("Física Básica");
  board.addSensor(new HallEffectSensor());
  board.setPreferences(&ftrlabPreferences);
  board.setup();
}

void loop()
{
  board.loop();
}
