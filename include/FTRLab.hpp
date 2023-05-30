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
const unsigned MEASUREMENT_MAX_SIZE = MEASUREMENT_MAX_LENGTH + 1;
// const unsigned MEASURE_OVERHEAD_LENGTH = 100; // Valor majorado
// const unsigned MEASURE_MAX_LENGTH = MEASUREMENT_MAX_LENGTH - MEASURE_OVERHEAD_LENGTH;
const unsigned BATTERY_INFO_MAX_LENGTH = 38;
const unsigned BATTERY_INFO_MAX_SIZE = BATTERY_INFO_MAX_LENGTH + 1;
const unsigned MAC_ADDRESS_MAX_SIZE = 11;
const unsigned CHIP_ID_MAX_SIZE = 18;

const uint16_t timerDivider = 80;
const unsigned clockFrequency = 800000000;
enum timers
{
  mdnsUpdate
};
const unsigned mdnsUpdateInterval = 30;

void IRAM_ATTR forceMdnsUpdate();
String getChipId();
void printNetworkInfo(WiFiClass Wifi, const char *ssid);

extern WiFiServer server;
extern WiFiClient client;

extern char chipId[CHIP_ID_MAX_SIZE];
extern hw_timer_t *mdnsUpdateTimer;

typedef struct
{
  unsigned index;
  time_t timestamp;
  String measure;
  /// @brief Retorna a string da medição. Caso seu length exceda MEASUREMENT_MAX_LENGTH, pode ter sido truncado.
  operator String() const
  {
    char measurementString[MEASUREMENT_MAX_SIZE + 1];
    snprintf(measurementString, MEASUREMENT_MAX_SIZE + 1, "{\"sensorIndex\":\"%u\",\"timestamp\":%li,\"value\":%s}", index, timestamp, measure);
    return String(measurementString);
  }
} Measurement;

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

class Sensor
{
public:
  String name;
  String quantity;

  virtual String takeMeasure() = 0;

private:
};

class Board
{
  const char *name;
  const char *ssid = "ITANET-CASTELO";
  const char *password = "c45t310a2";
  char macAddress[MAC_ADDRESS_MAX_SIZE];
  BatteryInfo batteryInfo = {.level = 70, .charging = true};

  std::vector<Sensor *> sensors;
  std::queue<Measurement> measurements;

public:
  Board(const char *name);
  void addSensor(Sensor *sensor);
  void setup();
  void loop();

private:
  void takeMeasurement(Sensor *sensor, unsigned index);
  void takeAllMeasurements();
  void sendMeasurements();
  void tcp();
  void setupMdns();
  void updateMdnsServiceTxtData();
  void printNetworkInfo();
  String getChipId();
};

#endif
