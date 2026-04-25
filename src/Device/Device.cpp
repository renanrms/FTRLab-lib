#include "FTRLab/Device.hpp"
#include "FTRLab/internals/getChipId.hpp"

Device::Device(
    INetworkProvider *networkProvider,
    IDiscoveryServiceProvider *discoveryServiceProvider,
    IKeyValueStoreProvider *keyValueStoreProvider,
    ITickerProvider *tickerProvider,
    ITimeProvider *timeProvider,
    IGpioProvider *gpioProvider)
    : networkProvider(networkProvider),
      discoveryServiceProvider(discoveryServiceProvider),
      keyValueStoreProvider(keyValueStoreProvider),
      tickerProvider(tickerProvider),
      timeProvider(timeProvider),
      gpioProvider(gpioProvider)
{
  this->chipId = getChipId();
  this->macAddress = this->networkProvider->macAddress();

  this->setTargetSampleRate(DEFAULT_SAMPLE_RATE);
  this->setTargetSendingFrequency(DEFAULT_SENDING_FREQUENCY);

  this->measurementsSemaphore = xSemaphoreCreateMutex();
  xSemaphoreGive(this->measurementsSemaphore);
}
