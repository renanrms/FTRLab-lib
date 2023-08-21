#include "FTRLab.hpp"

void Device::forceMdnsUpdate()
{
  // if (WiFi.status() == WL_CONNECTED && !this->client.connected())
  // {
  Serial.println("Sending mDNS forced update.");
  this->updateMdnsTxtData();
  // }
}
