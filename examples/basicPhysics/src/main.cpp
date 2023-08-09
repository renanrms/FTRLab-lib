#include "FTRLab.hpp"

#include "sensors/UltrasonicSensor.cpp"

Preferences ftrlabPreferences;

/**
 * Pinos GPIO utilizados no dispositivo.
 * Configure-os de acordo com a necessidade, observando pinos obrigatórios e restrições de hardware para os pinos escolhidos em cada função.
 */
enum PINS
{
  NETWORK_RECONFIGURATION_BUTTON = 5,
  NETWORK_STATUS_LED = 18,
  // Adicione aqui outros pinos utilizados pela placa
  ULTRASONIC_SENSOR_TRIGGER = 12,
  ULTRASONIC_SENSOR_ECHO = 13,
};

void setup()
{
  // Configuração de sensores, informações e pinos escolhidos para o dispositivo
  board.setName("Física Básica");
  board.addSensor(new UltrasonicSensor(PINS::ULTRASONIC_SENSOR_TRIGGER, PINS::ULTRASONIC_SENSOR_ECHO));
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

// A função fica livre caso queira executar alguma tarefa adicional.
void loop() {}
