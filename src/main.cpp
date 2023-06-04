#include "FTRLab.hpp"

#include "sensors/HallEffectSensor.cpp"

void setup()
{
  board.setName("Física Básica");
  board.addSensor(new HallEffectSensor());
  board.setup();
}

void loop()
{
  board.loop();
}
