#include "FTRLab/Device.hpp"

void Device::setTargetSendingFrequency(float frequency)
{
  this->targetSendingPeriod = 1000000 / frequency;
}
