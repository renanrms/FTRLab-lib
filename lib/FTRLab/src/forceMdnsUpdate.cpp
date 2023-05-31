#include "FTRLab.hpp"

extern char chipId[CHIP_ID_MAX_SIZE];

void IRAM_ATTR forceMdnsUpdate()
{
  Serial.print("Configurando nome... ");
  MDNS.setInstanceName(chipId);
  Serial.println("ok");
}
