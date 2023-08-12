#include "FTRLab.hpp"

void Device::forceMdnsUpdate()
{
  this->updateMdnsTxtData();
  Serial.println("New mDNS response emitted.");
}
