#ifndef FTR_Lab_H
#define FTR_Lab_H "FTR_Lab_H"

#include <Arduino.h>

#include <WiFi.h>
#include <ESPmDNS.h>

#include "FTRLab/BatteryInfo.hpp"
#include "FTRLab/Board.hpp"
#include "FTRLab/Measurement.hpp"
#include "FTRLab/Sensor.hpp"
#include "FTRLab/constants.hpp"

// void IRAM_ATTR forceMdnsUpdate();

// extern WiFiServer server;
// extern WiFiClient client;

// extern char chipId[CHIP_ID_MAX_SIZE];
// extern hw_timer_t *mdnsUpdateTimer;

extern Board board;

#endif
