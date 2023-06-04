#include "FTRLab/Board.hpp"

void Board::addSensor(Sensor *sensor)
{
  this->sensors.push_back(sensor);
}
