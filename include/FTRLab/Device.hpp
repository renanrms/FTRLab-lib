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
  /* Configura o nome do dispositivo */
  void setName(String name);
  /* Adiciona a instância de um sensor ao dispositivo para que fique disponível
  para utilização. */
  void addSensor(Sensor *sensor);
  /* Configura pinos as para funções básicas do dispositivo. */
  void setDevicePins(uint8_t networkButton, uint8_t networkLed);
  /* define frequência de amostragem. */
  void setTargetSampleRate(float frequency);
  /* define frequência de amostragem. */
  void setTargetSendingFrequency(float frequency);
  /* Configura o armazenamento utilizado com a biblioteca preferences.*/
  void setPreferencesStore(Preferences *preferencesStore);
  /* Faz toda a inicialização do dispositivo, iniciando as tarefas de medição e
  comunicação. */
  void setup();
  /* Força o envio de uma atualização mDNS. */
  void forceMdnsUpdate();
  /* Task de comunicação. Não deve ser chamada diretamente, pois faz parte do
  método setup. */
  void communicationTask();
  /* Task de medição. Não deve ser chamada diretamente, pois faz parte do método
  setup. */
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
 * Utilize as propriedades e os métodos públicos para controlar o funcionamento do dispositivo.
 * Crie e adicione sensores.
 *
 * Para instruções mais detalhadas veja exemplos da biblioteca em:
 * https://registry.platformio.org/libraries/renanrms/FTRLab/examples
 */
extern Device device;

#endif
