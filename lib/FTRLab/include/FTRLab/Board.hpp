#ifndef FTRLAB_BOARD_H
#define FTRLAB_BOARD_H "FTRLAB_BOARD_H"

#include <queue>
#include <vector>

#include <WiFi.h>
#include <ESPmDNS.h>
#include <ESPNtpClient.h>
#include <Ticker.h>
#include <Preferences.h>

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
  BatteryInfo *batteryInfo = NULL;
  Preferences *preferences = NULL;

  WiFiServer server = WiFiServer(PORT);
  WiFiClient client;
  Ticker mdnsUpdateTimer;

  std::vector<Sensor *> sensors;
  std::queue<Measurement> measurements;

  struct
  {
    uint8_t networkButton;
    uint8_t networkLed;
  } pins;

  Board();
  void setName(String name);
  void addSensor(Sensor *sensor);
  void setDevicePins(uint8_t networkButton, uint8_t networkLed);
  void setup();
  void loop();
  void forceMdnsUpdate();
  void connectToNetworkSmartConfig();
  void setPreferencesStore(Preferences *preferencesStore);

private:
  void takeMeasurement(Sensor *sensor, unsigned index);
  void takeAllMeasurements();
  void sendMeasurements();
  void tcp();
  void connectToNetwork();
  void setupMdns();
  void setupNTP();
  void updateMdnsServiceTxtData();
  void printBoardInfo();
  void printNetworkInfo();
  String getChipId();
};

extern Board board;

#endif
