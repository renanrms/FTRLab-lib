#include "FTR-Lab.hpp"

void Board::updateMdnsServiceTxtData()
{
  MDNS.addServiceTxt("_ftr-lab", "_tcp", "name", this->name);
  MDNS.addServiceTxt("_ftr-lab", "_tcp", "available", client.connected() ? "false" : "true");
  MDNS.addServiceTxt("_ftr-lab", "_tcp", "battery", this->batteryInfo);

  for (unsigned index = 0; index < this->sensors.size(); index++)
  {
    MDNS.addServiceTxt("_ftr-lab", "_tcp", "sensor[" + String(index) + "]", "{\"index\":" + String(index) + ",\"quantity\":\"" + this->sensors[index]->quantity + "\"}");
  }
}
