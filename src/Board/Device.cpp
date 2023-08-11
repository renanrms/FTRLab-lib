#include "FTRLab/Device.hpp"

Device::Device()
{
  this->macAddress = WiFi.macAddress();
  this->chipId = this->getChipId();

  this->setMinimumMeasurementPeriod(DEFAULT_TAKEING_PERIOD);
  this->setMaximumSendingPeriod(DEFAULT_SENDING_PERIOD);

  this->measurementsSemaphore = xSemaphoreCreateMutex();
  xSemaphoreGive(this->measurementsSemaphore);
}
