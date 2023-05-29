#include "FTR-Lab.hpp"

#include "sensors/HallEffectSensor.cpp"

Board *board;

void setup()
{
  std::vector<Sensor *> sensors;
  sensors.push_back(new HallEffectSensor());

  board = new Board("Física Básica", sensors);
}

void loop()
{
  board->loop();
}
