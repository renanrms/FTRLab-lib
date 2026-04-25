#include "FTRLab/Device.hpp"

void Device::printNetworkInfo()
{
  Serial.println("\n===== Network info =====");
  Serial.print("SSID: ");
  Serial.println(this->networkProvider->SSID().c_str());
  Serial.print("MAC address: ");
  Serial.println(this->networkProvider->macAddress().c_str());
  Serial.print("IP address: ");
  Serial.println(this->networkProvider->localIP().c_str());
  Serial.print("Subnet Mask: ");
  Serial.println(this->networkProvider->subnetMask().c_str());
  Serial.print("Gateway: ");
  Serial.println(this->networkProvider->gatewayIP().c_str());
  Serial.print("Broadcast: ");
  Serial.println(this->networkProvider->broadcastIP().c_str());
  Serial.print("DNS 1: ");
  Serial.println(this->networkProvider->dnsIP(0).c_str());
  Serial.print("DNS 2: ");
  Serial.println(this->networkProvider->dnsIP(1).c_str());
}
