#include "FTRLab.hpp"
#include "FTRLab/Boards/esp32/ESP32NetworkProvider.hpp"
#include "FTRLab/Boards/esp32/ESP32DiscoveryServiceProvider.hpp"
#include "FTRLab/Boards/esp32/ESP32KeyValueStoreProvider.hpp"
#include "FTRLab/Boards/esp32/ESP32TickerProvider.hpp"
#include "FTRLab/Boards/esp32/ESP32TimeProvider.hpp"
#include "FTRLab/Boards/esp32/ESP32GpioProvider.hpp"

static ESP32NetworkProvider networkProvider;
static ESP32DiscoveryServiceProvider discoveryServiceProvider;
static ESP32KeyValueStoreProvider keyValueStoreProvider;
static ESP32TickerProvider tickerProvider;
static ESP32TimeProvider timeProvider;
static ESP32GpioProvider gpioProvider;

Device device(
    &networkProvider,
    &discoveryServiceProvider,
    &keyValueStoreProvider,
    &tickerProvider,
    &timeProvider,
    &gpioProvider);
