#include "FTRLab/Device.hpp"

void Device::setTargetSampleRate(float frequency)
{
  this->targetTakeingPeriod = 1000 / frequency;
}
