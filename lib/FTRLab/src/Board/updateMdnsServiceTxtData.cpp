#include "FTRLab/Board.hpp"

void Board::updateMdnsServiceTxtData()
{
  MDNS.addServiceTxt(SERVICE_NAME, PROTOCOL, "name", this->name);
  MDNS.addServiceTxt(SERVICE_NAME, PROTOCOL, "available", client.connected() ? "false" : "true");

  if (this->batteryInfo != NULL)
  {
    MDNS.addServiceTxt(SERVICE_NAME, PROTOCOL, "battery", *(this->batteryInfo));
  }

  for (unsigned index = 0; index < this->sensors.size(); index++)
  {
    MDNS.addServiceTxt(SERVICE_NAME, PROTOCOL, "sensor[" + String(index) + "]", "{\"index\":" + String(index) + ",\"quantity\":\"" + this->sensors[index]->quantity + "\",\"name\":\"" + this->sensors[index]->name + "\"}");
  }
}
