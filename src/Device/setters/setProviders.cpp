#include "FTRLab/Device.hpp"

void Device::setNetworkProvider(INetworkProvider *networkProvider)
{
  this->networkProvider = networkProvider;
  this->macAddress = networkProvider->macAddress();
}

void Device::setDiscoveryServiceProvider(IDiscoveryServiceProvider *discoveryProvider)
{
  this->discoveryServiceProvider = discoveryProvider;
}

void Device::setTickerProvider(ITickerProvider *tickerProvider)
{
  this->tickerProvider = tickerProvider;
}

void Device::setTimeProvider(ITimeProvider *timeProvider)
{
  this->timeProvider = timeProvider;
}

void Device::setGpioProvider(IGpioProvider *gpioProvider)
{
  this->gpioProvider = gpioProvider;
}
