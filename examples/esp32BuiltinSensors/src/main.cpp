#include "FTRLab.hpp"

#include "sensors/HallEffectSensor.cpp"
#include "sensors/TemperatureBuiltInSensor.cpp"

Preferences ftrlabPreferences;

/**
 * Pinos GPIO utilizados no dispositivo.
 * Configure-os de acordo com a necessidade, observando pinos obrigatórios e restrições de hardware para os pinos escolhidos em cada função.
 */
enum PINS
{
  NETWORK_RECONFIGURATION_BUTTON = 5,
  NETWORK_STATUS_LED = 18,
};

void setup()
{
  // Configuração de sensores, informações e pinos escolhidos para o dispositivo
  device.setName("ESP32 Builtin");
  device.addSensor(new HallEffectSensor());
  device.addSensor(new TemperatureBuiltInSensor());
  device.setDevicePins(
      PINS::NETWORK_RECONFIGURATION_BUTTON,
      PINS::NETWORK_STATUS_LED);

  // Se necessário descomente as linhas abaixo e altere os valores para ajustar períodos de medição e envio
  // device.setMinimumMeasurementPeriod(10);
  // device.setMaximumSendingPeriod(200);

  // Setup do dispositivo (não alterar)
  ftrlabPreferences.begin("FRTLab");
  device.setPreferencesStore(&ftrlabPreferences);
  device.setup();
}

// A função fica livre caso queira executar alguma tarefa adicional.
void loop() {}
