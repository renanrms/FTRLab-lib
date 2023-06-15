#include "FTRLab.hpp"

#include "sensors/HallEffectSensor.cpp"

Preferences ftrlabPreferences;

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
