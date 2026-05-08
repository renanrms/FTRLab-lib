#include "FTRLab/Device.hpp"

void Device::updateMdnsTxtData()
{
  this->discoveryServiceProvider->addServiceTxt(SERVICE_NAME.c_str(), PROTOCOL.c_str(), "name", this->name.c_str());
  this->discoveryServiceProvider->addServiceTxt(SERVICE_NAME.c_str(), PROTOCOL.c_str(), "available",
                                                this->networkProvider->clientConnected() ? "false" : "true");
  this->discoveryServiceProvider->addServiceTxt(SERVICE_NAME.c_str(), PROTOCOL.c_str(), "timeSynced",
                                                this->timeSynced ? "true" : "false");

  if (this->batteryInfo != nullptr)
  {
    this->discoveryServiceProvider->addServiceTxt(SERVICE_NAME.c_str(), PROTOCOL.c_str(), "battery",
                                                  String(*(this->batteryInfo)).c_str());
  }

  for (unsigned index = 0; index < this->sensors.size(); index++)
  {
    String sensorJson = "{\"index\":" + String((unsigned int)index) +
                        ",\"quantity\":\"" + this->sensors[index]->quantity +
                        "\",\"method\":\"" + this->sensors[index]->method + "\"}";
    String key = "sensor[" + String((unsigned int)index) + "]";
    this->discoveryServiceProvider->addServiceTxt(SERVICE_NAME.c_str(), PROTOCOL.c_str(),
                                                  key.c_str(), sensorJson.c_str());
  }
}
