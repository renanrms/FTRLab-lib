#ifndef FTR_Lab_H
#define FTR_Lab_H "FTR_Lab_H"

#include <Arduino.h>
#include <queue>
#include <vector>
#include <WiFi.h>
#include <ESPmDNS.h>

/**
 * Constantes terminadas em "LENGTH", são tamanhos úteis (não consideram o caractere de terminação).
 * Constantes terminadas em "SIZE", são tamanhos totais (consideram o caractere de terminação).
 */

const unsigned PAYLOAD_MAX_LENGTH = 1024;
const unsigned MEASUREMENT_OVERHEAD_LENGTH = 21;
const unsigned MEASUREMENT_MAX_LENGTH = PAYLOAD_MAX_LENGTH - MEASUREMENT_OVERHEAD_LENGTH;
// const unsigned MEASURE_OVERHEAD_LENGTH = 100; // Valor majorado
// const unsigned MEASURE_MAX_LENGTH = MEASUREMENT_MAX_LENGTH - MEASURE_OVERHEAD_LENGTH;
const unsigned MAC_ADDRESS_MAX_SIZE = 11;
const unsigned CHIP_ID_MAX_SIZE = 18;

const uint16_t timerDivider = 80;
const unsigned clockFrequency = 800000000;
enum timers
{
  mdnsUpdate
};
const unsigned mdnsUpdateInterval = 30;

typedef struct
{
  unsigned index;
  time_t timestamp;
  String measure;
  /// @brief Retorna a string da medição. Caso seu length exceda MEASUREMENT_MAX_LENGTH, pode ter sido truncado.
  operator String() const
  {
    char measurementString[MEASUREMENT_MAX_LENGTH + 2];
    snprintf(measurementString, MEASUREMENT_MAX_LENGTH + 2, "{\"sensorIndex\":\"%u\",\"timestamp\":%li,\"value\":%s}", index, timestamp, measure);
    return String(measurementString);
  }
} Measurement;

class Sensor
{
  const char *name;
  const char *quantity;

public:
  // Sensor(){};
  virtual String takeMeasure() = 0;

private:
};

class Board
{
  const char *name;
  const char *ssid = "ITANET-CASTELO";
  const char *password = "c45t310a2";
  char macAddress[MAC_ADDRESS_MAX_SIZE];

  std::vector<Sensor *> sensors;
  std::queue<Measurement> measurements;

public:
  Board(const char *name, const std::vector<Sensor *> sensors);
  void takeMeasurement(Sensor *sensor, unsigned index);
  void takeAllMeasurements();
  void sendMeasurements();
  void loop();
  void tcp();

private:
  void setupMdns();
};

void IRAM_ATTR forceMdnsUpdate();

#endif
