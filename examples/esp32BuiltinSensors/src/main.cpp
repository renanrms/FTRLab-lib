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
  board.setName("ESP32 Builtin");
  board.addSensor(new HallEffectSensor());
  board.addSensor(new TemperatureBuiltInSensor());
  board.setDevicePins(
      PINS::NETWORK_RECONFIGURATION_BUTTON,
      PINS::NETWORK_STATUS_LED);

  // Se necessário descomente as linhas abaixo e altere os valores para ajustar períodos de medição e envio
  // board.setMinimumMeasurementPeriod(10000);
  // board.setMeasurementSendingPeriod(100000);

  // Setup do dispositivo (não alterar)
  ftrlabPreferences.begin("FRTLab");
  board.setPreferencesStore(&ftrlabPreferences);
  board.setup();
}

void loop()
{
  // A linha abaixo deve ser chamada a cada iteração do loop
  board.loop();
}
