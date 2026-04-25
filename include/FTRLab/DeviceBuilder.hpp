#ifndef FTRLAB_DEVICE_BUILDER_H
#define FTRLAB_DEVICE_BUILDER_H

#include <cassert>
#include "FTRLab/Device.hpp"

/**
 * Constrói um Device passo a passo, garantindo que todos os providers
 * obrigatórios estejam presentes antes de entregar o objeto.
 *
 * Uso:
 *   Device* d = DeviceBuilder()
 *       .withNetworkProvider(...)
 *       .withName("Sensor")
 *       .build();
 */
class DeviceBuilder
{
public:
  DeviceBuilder &withNetworkProvider(INetworkProvider *provider)
  {
    networkProvider_ = provider;
    return *this;
  }

  DeviceBuilder &withDiscoveryServiceProvider(IDiscoveryServiceProvider *provider)
  {
    discoveryServiceProvider_ = provider;
    return *this;
  }

  DeviceBuilder &withKeyValueStoreProvider(IKeyValueStoreProvider *provider)
  {
    keyValueStoreProvider_ = provider;
    return *this;
  }

  DeviceBuilder &withTickerProvider(ITickerProvider *provider)
  {
    tickerProvider_ = provider;
    return *this;
  }

  DeviceBuilder &withTimeProvider(ITimeProvider *provider)
  {
    timeProvider_ = provider;
    return *this;
  }

  DeviceBuilder &withGpioProvider(IGpioProvider *provider)
  {
    gpioProvider_ = provider;
    return *this;
  }

  Device *build()
  {
    assert(networkProvider_ != nullptr);
    assert(discoveryServiceProvider_ != nullptr);
    assert(keyValueStoreProvider_ != nullptr);
    assert(tickerProvider_ != nullptr);
    assert(timeProvider_ != nullptr);
    assert(gpioProvider_ != nullptr);

    Device *device = new Device();
    device->setNetworkProvider(networkProvider_);
    device->setDiscoveryServiceProvider(discoveryServiceProvider_);
    device->setKeyValueStoreProvider(keyValueStoreProvider_);
    device->setTickerProvider(tickerProvider_);
    device->setTimeProvider(timeProvider_);
    device->setGpioProvider(gpioProvider_);

    return device;
  }

protected:
  INetworkProvider *networkProvider_ = nullptr;
  IDiscoveryServiceProvider *discoveryServiceProvider_ = nullptr;
  IKeyValueStoreProvider *keyValueStoreProvider_ = nullptr;
  ITickerProvider *tickerProvider_ = nullptr;
  ITimeProvider *timeProvider_ = nullptr;
  IGpioProvider *gpioProvider_ = nullptr;
};

#endif
