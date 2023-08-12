#include "FTRLab/Device.hpp"

void Device::updateMdnsTxtData()
{
  MDNS.addServiceTxt(SERVICE_NAME, PROTOCOL, "name", this->name);
  MDNS.addServiceTxt(SERVICE_NAME, PROTOCOL, "available", client.connected() ? "false" : "true");
  MDNS.addServiceTxt(SERVICE_NAME, PROTOCOL, "timeSynced", this->timeSynced ? "true" : "false");

  if (this->batteryInfo != NULL)
  {
    MDNS.addServiceTxt(SERVICE_NAME, PROTOCOL, "battery", *(this->batteryInfo));
  }

  for (unsigned index = 0; index < this->sensors.size(); index++)
  {
    MDNS.addServiceTxt(SERVICE_NAME, PROTOCOL, "sensor[" + String(index) + "]", "{\"index\":" + String(index) + ",\"quantity\":\"" + this->sensors[index]->quantity + "\",\"method\":\"" + this->sensors[index]->method + "\"}");
  }
}
