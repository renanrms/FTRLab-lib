#ifndef FTRLAB_BATTERY_INFO_H
#define FTRLAB_BATTERY_INFO_H "FTRLAB_BATTERY_INFO_H"

#include "constants.hpp"

typedef struct
{
  unsigned level;
  bool charging;
  operator String() const
  {
    char batteryInfoString[BATTERY_INFO_MAX_SIZE];
    snprintf(batteryInfoString, BATTERY_INFO_MAX_SIZE, "{\"level\":%u,\"charging\":%s}", level, charging ? "true" : "false");
    return String(batteryInfoString);
  }
} BatteryInfo;

#endif
