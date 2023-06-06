#ifndef FTRLAB_BOARD_H
#define FTRLAB_BOARD_H "FTRLAB_BOARD_H"

#include <queue>
#include <vector>

#include <WiFi.h>
#include <ESPmDNS.h>
#include <ESPNtpClient.h>
#include <Ticker.h>

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
  String ssid = "wPESC-Visitante";
  String password = "";
  BatteryInfo *batteryInfo = NULL;

  WiFiServer server = WiFiServer(PORT);
  WiFiClient client;
  Ticker mdnsUpdateTimer;

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
  void connectToNetwork();
  void setupMdns();
  void updateMdnsServiceTxtData();
  void printBoardInfo();
  void printNetworkInfo();
  String getChipId();
};

extern Board board;

#endif
