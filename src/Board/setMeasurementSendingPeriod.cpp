#include "FTRLab/Board.hpp"

void Board::setMaximumSendingPeriod(int64_t periodMs)
{
  this->maximumSendingPeriod = periodMs;
  this->targetSendingPeriod = periodMs;
}
