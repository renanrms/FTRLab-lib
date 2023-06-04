#ifndef FTRLAB_BOARD_H
#define FTRLAB_BOARD_H "FTRLAB_BOARD_H"

#include <queue>
#include <vector>

#include <WiFi.h>
#include <ESPmDNS.h>

#include "constants.hpp"
#include "Sensor.hpp"
#include "BatteryInfo.hpp"
#include "Measurement.hpp"

class Board
{
public:
  String name;
  String chipId;
  String macAddress;
  String wifiSsid = "ITANET-CASTELO";
  String password = "c45t310a2";
  BatteryInfo *batteryInfo = NULL;

  WiFiServer server = WiFiServer(PORT);
  WiFiClient client;
  hw_timer_t *mdnsUpdateTimer = NULL;

  std::vector<Sensor *> sensors;
  std::queue<Measurement> measurements;

  Board();
  void setName(String name);
  void addSensor(Sensor *sensor);
  void setup();
  void loop();
  void forceMdnsUpdate();

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

extern Board board;

#endif
