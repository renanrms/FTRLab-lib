#include "FTRLab.hpp"

#include "sensors/HallEffectSensor.cpp"

Board board = Board("Física Básica");

void setup()
{
  board.addSensor(new HallEffectSensor());
  board.setup();
}

void loop()
{
  board.loop();
}
