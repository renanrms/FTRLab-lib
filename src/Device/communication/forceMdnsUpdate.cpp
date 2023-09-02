#include "FTRLab.hpp"

void Device::forceMdnsUpdate()
{
  Serial.println("Sending mDNS forced update.");
  this->updateMdnsTxtData();
}
