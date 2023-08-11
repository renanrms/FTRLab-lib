#include "FTRLab.hpp"

void Board::forceMdnsUpdate()
{
  this->updateMdnsServiceTxtData();
  Serial.println("New mDNS response emitted.");
}
