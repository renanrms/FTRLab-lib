#include "FTRLab/Device.hpp"
#include "FTRLab/internals/getChipId.hpp"

Device::Device()
{
  this->macAddress = WiFi.macAddress();
  this->chipId = getChipId();

  this->setMinimumMeasurementPeriod(DEFAULT_TAKEING_PERIOD);
  this->setMaximumSendingPeriod(DEFAULT_SENDING_PERIOD);

  this->measurementsSemaphore = xSemaphoreCreateMutex();
  xSemaphoreGive(this->measurementsSemaphore);
}
