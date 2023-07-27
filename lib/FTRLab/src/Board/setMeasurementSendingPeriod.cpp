#include "FTRLab/Board.hpp"

void Board::setMeasurementSendingPeriod(int64_t periodUs)
{
  this->measurementSendingPeriod = periodUs;
}
