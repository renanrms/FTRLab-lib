#include "FTRLab/Board.hpp"

void Board::loop()
{
  this->tcp();
  if (this->client.connected())
  {
    this->takeAllMeasurements();
    this->sendMeasurements();
  }
  delay(200);
}
