#ifndef FTRLAB_BOARDS_ESP32_DEVICE_BUILDER_H
#define FTRLAB_BOARDS_ESP32_DEVICE_BUILDER_H

#include "FTRLab/DeviceBuilder.hpp"
#include "FTRLab/boards/esp32/ESP32NetworkProvider.hpp"
#include "FTRLab/boards/esp32/ESP32DiscoveryServiceProvider.hpp"
#include "FTRLab/boards/esp32/ESP32KeyValueStoreProvider.hpp"
#include "FTRLab/boards/esp32/ESP32TickerProvider.hpp"
#include "FTRLab/boards/esp32/ESP32TimeProvider.hpp"
#include "FTRLab/boards/esp32/ESP32GpioProvider.hpp"

/**
 * Builder pré-configurado com os providers do ESP32.
 *
 * Uso:
 *   Device* d = ESP32DeviceBuilder().build();
 */
class ESP32DeviceBuilder : public DeviceBuilder
{
public:
  ESP32DeviceBuilder()
  {
    withNetworkProvider(new ESP32NetworkProvider());
    withDiscoveryServiceProvider(new ESP32DiscoveryServiceProvider());
    withKeyValueStoreProvider(new ESP32KeyValueStoreProvider());
    withTickerProvider(new ESP32TickerProvider());
    withTimeProvider(new ESP32TimeProvider());
    withGpioProvider(new ESP32GpioProvider());
  }
};

#endif
