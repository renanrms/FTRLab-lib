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
  device.setName("Distância HC-SR04");
  device.addSensor(new UltrasonicSensor(PINS::ULTRASONIC_SENSOR_TRIGGER, PINS::ULTRASONIC_SENSOR_ECHO));
  device.setDevicePins(
      PINS::NETWORK_RECONFIGURATION_BUTTON,
      PINS::NETWORK_STATUS_LED);

  // Configurações opcionais
  device.setTargetSampleRate(80);

  // Setup do dispositivo (não alterar)
  ftrlabPreferences.begin("FRTLab");
  device.setPreferencesStore(&ftrlabPreferences);
  device.setup();
}

// A função loop é obrigatória, mas o código dentro dela não será alcançado.
void loop() {}
