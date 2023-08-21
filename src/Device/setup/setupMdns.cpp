#include "FTRLab/Device.hpp"
#include "FTRLab/internals/forceMdnsUpdateWrapper.hpp"

void Device::setupMdns()
{
  if (!MDNS.begin(this->chipId.c_str()))
  {
    Serial.println("Error setting up mDNS responder!");
    while (true)
    {
      delay(1000);
    }
  }

  Serial.println("\n===== Adding mDNS service =====");
  Serial.println("Name: " + SERVICE_NAME);
  Serial.println("Protocol: " + PROTOCOL);
  Serial.println("Port: " + String(PORT));
  Serial.println();

  MDNS.addService(SERVICE_NAME, PROTOCOL, PORT);

  this->updateMdnsTxtData();

  this->mdnsUpdateTimer.attach_ms(MDNS_FORCED_UPDATE_INTERVAL, &forceMdnsUpdateWrapper);
}
