#include "FTR-Lab.hpp"

#include "sensors/HallEffectSensor.cpp"

Board *board;

void setup()
{
  board = new Board("Física Básica");
  board->addSensor(new HallEffectSensor());
  board->setup();
}

void loop()
{
  board->loop();
}
