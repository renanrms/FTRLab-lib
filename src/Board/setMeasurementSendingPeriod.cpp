#include "FTRLab/Board.hpp"

void Board::setMeasurementSendingPeriod(int64_t periodMs)
{
  this->targetSendingPeriod = periodMs;
}
