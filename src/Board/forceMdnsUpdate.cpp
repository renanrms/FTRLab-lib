#include "FTRLab.hpp"

void Device::forceMdnsUpdate()
{
  this->updateMdnsServiceTxtData();
  Serial.println("New mDNS response emitted.");
}
