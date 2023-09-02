#ifndef FTRLAB_DEVICE_H
#define FTRLAB_DEVICE_H "FTRLAB_DEVICE_H"

#include <Arduino.h>

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

/**
 * Classe Device
 *
 * Manipula todo o funcionamento do dispositivo FTRLab.
 *
 * Não deve ser criada uma segunda instância desta classe, uma vez que manipula
 * recursos globais do microcontrolador, como conexão de rede. Utilize-a através
 * da instância declarada globalmente.
 */
class Device
{
public:
  Device();
  void setName(String name);
  void addSensor(Sensor *sensor);
  void setDevicePins(uint8_t networkButton, uint8_t networkLed);
  void setTargetSampleRate(float frequency);
  void setTargetSendingFrequency(float frequency);
  void setPreferencesStore(Preferences *preferencesStore);
  void setup();
  void forceMdnsUpdate();
  void communicationTask();
  void measurementTask();

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
  int64_t targetSendingPeriod;

  void takeMeasurement(Sensor *sensor, unsigned index);
  void takeAllMeasurements();
  unsigned int sendMeasurementsBatch();
  unsigned int sendMeasurements();
  void connectToWifi();
  void doSmartConfig();
  void setupMdns();
  void setupNTP();
  void updateMdnsTxtData();
  void printDeviceInfo();
  void printNetworkInfo();
};

/**
 * Instância de dispositivo FTRLab disponível globalmente.
 *
 * Utilize os membros públicos para controlar o funcionamento do dispositivo.
 * Crie e adicione sensores ao device.
 *
 * Para instruções mais detalhadas veja exemplos da biblioteca em:
 * https://registry.platformio.org/libraries/renanrms/FTRLab/examples
 */
extern Device device;

#endif
