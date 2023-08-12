#include "FTRLab/Device.hpp"

void Device::printDeviceInfo()
{
  Serial.println("\n===== FTRLab device infos =====");
  Serial.println("Id: " + this->chipId);
  Serial.println("Name: " + this->name);
  Serial.println("Sensors:");

  Serial.println("Index\tQuantity\tMethod");

  for (unsigned index = 0; index < this->sensors.size(); index++)
  {
    Serial.println(String(index) + "\t" + this->sensors[index]->quantity + "\t" + this->sensors[index]->method);
  }

  Serial.println();
}
