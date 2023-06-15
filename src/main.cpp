#include "FTRLab.hpp"

#include "sensors/HallEffectSensor.cpp"

Preferences ftrlabPreferences;

// enum DEVICE_PINS
// {
//   CONFIGURE_NETWORK_BUTTON = 18,
// };

void setup()
{
  // Configuração de sensores e nome do dispositivo
  board.setName("Física Básica");
  board.addSensor(new HallEffectSensor());

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
