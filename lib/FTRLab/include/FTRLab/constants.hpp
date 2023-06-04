#ifndef FTRLAB_CONSTANTS_H
#define FTRLAB_CONSTANTS_H "FTRLAB_CONSTANTS_H"

#include <Arduino.h>

/**
 * Constantes terminadas em "LENGTH", são tamanhos úteis (não consideram o caractere de terminação).
 * Constantes terminadas em "SIZE", são tamanhos totais (consideram o caractere de terminação).
 */

const unsigned PAYLOAD_MAX_LENGTH = 1024;
const unsigned MEASUREMENT_OVERHEAD_LENGTH = 21;
const unsigned MEASUREMENT_MAX_LENGTH = PAYLOAD_MAX_LENGTH - MEASUREMENT_OVERHEAD_LENGTH;
const unsigned MEASUREMENT_MAX_SIZE = MEASUREMENT_MAX_LENGTH + 1;
// const unsigned MEASURE_OVERHEAD_LENGTH = 100; // Valor majorado
// const unsigned MEASURE_MAX_LENGTH = MEASUREMENT_MAX_LENGTH - MEASURE_OVERHEAD_LENGTH;
const unsigned BATTERY_INFO_MAX_LENGTH = 38;
const unsigned BATTERY_INFO_MAX_SIZE = BATTERY_INFO_MAX_LENGTH + 1;

const uint16_t PORT = 3333;
const String PROTOCOL = "_tcp";
const String SERVICE_NAME = "_ftr-lab";

const uint16_t timerDivider = 80;
const unsigned clockFrequency = 800000000;
enum timers
{
  mdnsUpdate
};
const unsigned mdnsUpdateInterval = 30;

#endif
