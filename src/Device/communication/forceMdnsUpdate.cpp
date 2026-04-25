#include "FTRLab/Device.hpp"

void Device::forceMdnsUpdate()
{
  Serial.println("Sending mDNS forced update.");
  this->updateMdnsTxtData();
}
