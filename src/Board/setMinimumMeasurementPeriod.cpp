#include "FTRLab/Board.hpp"

void Board::setMinimumMeasurementPeriod(int64_t periodMs)
{
  this->targetTakeingPeriod = periodMs;
}
