#ifndef FTRLAB_BOARD_H
#define FTRLAB_BOARD_H "FTRLAB_BOARD_H"

#include <queue>
#include <vector>

#include "constants.hpp"
#include "Sensor.hpp"
#include "BatteryInfo.hpp"
#include "Measurement.hpp"

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
  Board();
  void setName(const char *name);
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
