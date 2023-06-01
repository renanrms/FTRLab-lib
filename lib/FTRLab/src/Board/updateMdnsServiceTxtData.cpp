#include "FTRLab/Board.hpp"

void Board::updateMdnsServiceTxtData()
{
  MDNS.addServiceTxt(MDNS_SERVICE_NAME, "_tcp", "name", this->name);
  MDNS.addServiceTxt(MDNS_SERVICE_NAME, "_tcp", "available", client.connected() ? "false" : "true");
  MDNS.addServiceTxt(MDNS_SERVICE_NAME, "_tcp", "battery", this->batteryInfo);

  for (unsigned index = 0; index < this->sensors.size(); index++)
  {
    MDNS.addServiceTxt(MDNS_SERVICE_NAME, "_tcp", "sensor[" + String(index) + "]", "{\"index\":" + String(index) + ",\"quantity\":\"" + this->sensors[index]->quantity + "\"}");
  }
}
