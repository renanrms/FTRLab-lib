#include "FTRLab/Device.hpp"
#include "FTRLab/internals/getChipId.hpp"

Device::Device()
{
  this->macAddress = WiFi.macAddress();
  this->chipId = getChipId();

  this->setTargetSampleRate(DEFAULT_SAMPLE_RATE);
  this->setTargetSendingFrequency(DEFAULT_SENDING_FREQUENCY);

  this->measurementsSemaphore = xSemaphoreCreateMutex();
  xSemaphoreGive(this->measurementsSemaphore);
}
