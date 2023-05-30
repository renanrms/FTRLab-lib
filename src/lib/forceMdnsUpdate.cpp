#include "FTR-Lab.hpp"

void IRAM_ATTR forceMdnsUpdate()
{
  Serial.print("Configurando nome... ");
  MDNS.setInstanceName(chipId);
  Serial.println("ok");
}
