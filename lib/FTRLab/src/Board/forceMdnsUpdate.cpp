#include "FTRLab.hpp"

void Board::forceMdnsUpdate()
{
  MDNS.setInstanceName(this->chipId);
  Serial.println("Emitida nova resposta mDNS periódica.");
}
