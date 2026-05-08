#include "FTRLab/Device.hpp"
#include "FTRLab/internals/getChipId.hpp"

Device *Device::instance_ = nullptr;

Device *Device::getInstance()
{
  if (instance_ == nullptr)
    instance_ = new Device();
  return instance_;
}

void Device::resetInstance()
{
  delete instance_;
  instance_ = nullptr;
}

Device::Device()
    : networkProvider(nullptr),
      discoveryServiceProvider(nullptr),
      keyValueStoreProvider(nullptr),
      tickerProvider(nullptr),
      timeProvider(nullptr),
      gpioProvider(nullptr)
{
  this->chipId = getChipId();
  this->setTargetSampleRate(DEFAULT_SAMPLE_RATE);
  this->setTargetSendingFrequency(DEFAULT_SENDING_FREQUENCY);
  this->measurementsSemaphore = xSemaphoreCreateMutex();
  xSemaphoreGive(this->measurementsSemaphore);
}
