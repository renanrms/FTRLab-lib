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
  bool timeSynced = false;
  int64_t targetTakeingPeriod = DEFAULT_TAKEING_PERIOD;
  int64_t targetSendingPeriod = DEFAULT_SENDING_PERIOD;

  WiFiServer server = WiFiServer(PORT);
  WiFiClient client;
  Ticker mdnsUpdateTimer;
  SemaphoreHandle_t measurementsQueue;

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
  void setMinimumMeasurementPeriod(int64_t periodMs);
  void setMeasurementSendingPeriod(int64_t periodMs);
  void setup();
  void communicationHandler();
  void measurementHandler();
  void forceMdnsUpdate();
  void setPreferencesStore(Preferences *preferencesStore);

private:
  void takeMeasurement(Sensor *sensor, unsigned index);
  void takeAllMeasurements();
  void sendMeasurementsBatch();
  void sendMeasurements();
  void connectToNetwork();
  void connectToNetworkSmartConfig();
  void setupMdns();
  void setupNTP();
  void updateMdnsServiceTxtData();
  void printBoardInfo();
  void printNetworkInfo();
  String getChipId();
};

extern Board board;

#endif
