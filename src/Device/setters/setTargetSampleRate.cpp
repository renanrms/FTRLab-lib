#include "FTRLab/Device.hpp"

void Device::setTargetSampleRate(float frequency)
{
  this->targetTakingPeriod = 1000000 / frequency;
}
