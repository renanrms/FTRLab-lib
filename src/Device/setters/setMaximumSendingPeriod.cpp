#include "FTRLab/Device.hpp"

void Device::setMaximumSendingPeriod(int64_t periodMs)
{
  this->maximumSendingPeriod = periodMs;
  this->targetSendingPeriod = periodMs;
}
