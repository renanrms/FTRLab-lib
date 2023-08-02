#include "FTRLab.hpp"

void Board::forceMdnsUpdate()
{
  MDNS.setInstanceName(this->chipId);
  Serial.println("New mDNS periodic response emitted.");
}
