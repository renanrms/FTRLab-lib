#include "FTRLab.hpp"
#include "FTRLab/boards/esp32/ESP32DeviceBuilder.hpp"

static Device *deviceInstance = ESP32DeviceBuilder().build();
Device &device = *deviceInstance;
