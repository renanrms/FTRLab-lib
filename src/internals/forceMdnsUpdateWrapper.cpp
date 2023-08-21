#include <Arduino.h>

#include "FTRLab/Device.hpp"
#include "FTRLab/internals/forceMdnsUpdateWrapper.hpp"

void IRAM_ATTR forceMdnsUpdateWrapper()
{
  device.forceMdnsUpdate();
}
