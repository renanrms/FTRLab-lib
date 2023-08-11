#ifndef FTRLAB_DEVICE_H
#define FTRLAB_DEVICE_H "FTRLAB_DEVICE_H"

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

class Device
{
public:
  Device();
  void setName(String name);
  void addSensor(Sensor *sensor);
  void setDevicePins(uint8_t networkButton, uint8_t networkLed);
  void setMinimumMeasurementPeriod(int64_t periodMs);
  void setMaximumSendingPeriod(int64_t periodMs);
  void setup();
  void communicationTask();
  void measurementTask();
  void forceMdnsUpdate();
  void setPreferencesStore(Preferences *preferencesStore);

private:
  String name;
  String chipId;
  String macAddress;
  BatteryInfo *batteryInfo = NULL;
  bool timeSynced = false;

  WiFiServer server = WiFiServer(PORT);
  WiFiClient client;

  std::vector<Sensor *> sensors;
  std::queue<Measurement> measurements;

  struct
  {
    uint8_t networkButton;
    uint8_t networkLed;
  } pins;

  Ticker mdnsUpdateTimer;
  SemaphoreHandle_t measurementsSemaphore;
  Preferences *preferences = NULL;
  TaskHandle_t communicationHandle;
  TaskHandle_t measurementHandle;

  int64_t targetTakeingPeriod;
  int64_t maximumSendingPeriod;
  int64_t targetSendingPeriod;

  void takeMeasurement(Sensor *sensor, unsigned index);
  void takeAllMeasurements();
  void sendMeasurementsBatch();
  void sendMeasurements();
  void connectToNetwork();
  void connectToNetworkSmartConfig();
  void setupMdns();
  void setupNTP();
  void updateMdnsServiceTxtData();
  void printDeviceInfo();
  void printNetworkInfo();
  String getChipId();
};

extern Device device;

#endif
