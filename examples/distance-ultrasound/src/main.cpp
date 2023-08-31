#include "FTRLab.hpp"

#include "sensors/HCSR04.cpp"

Preferences ftrlabPreferences;

/**
 * Pinos GPIO utilizados no dispositivo.
 * Configure-os de acordo com a necessidade, observando pinos obrigatórios e restrições de hardware para os pinos escolhidos em cada função.
 */
enum PINS
{
  CONFIGURATION_BUTTON = 5,
  STATUS_LED = 18,
  // Adicione aqui outros pinos utilizados pela placa
  TRIGGER = 12,
  ECHO = 13,
};

void setup()
{
  // Configuração de sensores, informações e pinos escolhidos para o dispositivo
  device.setName("Distância HC-SR04");
  device.addSensor(new HCSR04(PINS::TRIGGER, PINS::ECHO));
  device.setDevicePins(PINS::CONFIGURATION_BUTTON, PINS::STATUS_LED);

  // Configurações opcionais
  device.setTargetSampleRate(80);

  // Setup do dispositivo (não alterar)
  ftrlabPreferences.begin("FRTLab");
  device.setPreferencesStore(&ftrlabPreferences);
  device.setup();
}

// A função loop é obrigatória, mas o código dentro dela não será alcançado.
void loop() {}
