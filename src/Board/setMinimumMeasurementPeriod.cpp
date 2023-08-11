#include "FTRLab/Device.hpp"

void Device::setMinimumMeasurementPeriod(int64_t periodMs)
{
  this->targetTakeingPeriod = periodMs;
}
