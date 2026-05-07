#ifndef FTRLAB_DEVICE_H
#define FTRLAB_DEVICE_H

#include <Arduino.h>
#include <queue>
#include <vector>

#include "constants.hpp"
#include "Sensor.hpp"
#include "BatteryInfo.hpp"
#include "Measurement.hpp"

#include "interfaces/INetworkProvider.hpp"
#include "interfaces/IDiscoveryServiceProvider.hpp"
#include "interfaces/IKeyValueStoreProvider.hpp"
#include "interfaces/ITickerProvider.hpp"
#include "interfaces/ITimeProvider.hpp"
#include "interfaces/IGpioProvider.hpp"

/**
 * Classe Device — Singleton
 *
 * Manipula todo o funcionamento do dispositivo FTRLab.
 * Garante uma única instância via getInstance(), criada pelo DeviceBuilder.
 */
class Device
{
public:
  Device();

  static Device *getInstance();

  /* Reseta a instância singleton (uso exclusivo em testes). */
  static void resetInstance();

  /* Configura o nome do dispositivo. */
  void setName(String name);

  /* Adiciona um sensor ao dispositivo. */
  void addSensor(Sensor *sensor);

  /* Configura os pinos para funções básicas do dispositivo. */
  void setDevicePins(uint8_t networkButton, uint8_t networkLed);

  /* Define a frequência de amostragem em Hz. */
  void setTargetSampleRate(float frequency);

  /* Define a frequência de envio em Hz. */
  void setTargetSendingFrequency(float frequency);

  /* Substitui o armazenamento de credenciais WiFi após a construção. */
  void setKeyValueStoreProvider(IKeyValueStoreProvider *provider);

  /* Substitui um provider após a construção (útil em testes). */
  void setNetworkProvider(INetworkProvider *networkProvider);
  void setDiscoveryServiceProvider(IDiscoveryServiceProvider *discoveryProvider);
  void setTickerProvider(ITickerProvider *tickerProvider);
  void setTimeProvider(ITimeProvider *timeProvider);
  void setGpioProvider(IGpioProvider *gpioProvider);

  /* Inicializa o dispositivo e inicia as tarefas de medição e comunicação. */
  void setup();

  /* Força o envio de uma atualização mDNS. */
  void forceMdnsUpdate();

  /* Tasks chamadas internamente pelo setup(). */
  void communicationTask();
  void measurementTask();

  void printDeviceInfo();

  String name;
  String chipId;
  BatteryInfo *batteryInfo = nullptr;

  std::vector<Sensor *> sensors;
  std::queue<Measurement> measurements;
  int64_t targetTakingPeriod;
  SemaphoreHandle_t measurementsSemaphore;
  void takeMeasurement(Sensor *sensor, unsigned index);
  void takeAllMeasurements();

  int64_t targetSendingPeriod;
  unsigned int sendMeasurementsBatch();
  unsigned int sendMeasurements();

  INetworkProvider *networkProvider;
  IDiscoveryServiceProvider *discoveryServiceProvider;
  IKeyValueStoreProvider *keyValueStoreProvider;
  ITickerProvider *tickerProvider;
  ITimeProvider *timeProvider;
  IGpioProvider *gpioProvider;

  TaskHandle_t communicationHandle;

  String macAddress;
  bool timeSynced = false;
  struct
  {
    uint8_t networkButton;
    uint8_t networkLed;
  } pins;

  void connectToWifi();
  void doSmartConfig();
  void setupMdns();
  void setupNTP();
  void updateMdnsTxtData();
  void printNetworkInfo();

private:
  static Device *instance_;
};

#endif
