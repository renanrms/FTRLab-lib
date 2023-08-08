#include "FTRLab/Board.hpp"

void Board::sendAllMeasurements()
{
  while (!this->measurements.empty())
  {
    this->sendMeasurementsBatch();
  }
}
