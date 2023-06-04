#include "FTRLab/Board.hpp"

void IRAM_ATTR forceMdnsUpdateWrapper()
{
  board.forceMdnsUpdate();
}

void Board::setupMdns()
{
  if (!MDNS.begin(this->chipId.c_str()))
  {
    Serial.println("Error setting up mDNS responder!");
    while (1)
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
  updateMdnsServiceTxtData();

  // Configura um timer para periodicamente setar o nome e forçar uma nova resposta MDNS.
  mdnsUpdateTimer = timerBegin(timers::mdnsUpdate, timerDivider, true);
  timerAttachInterrupt(mdnsUpdateTimer, &forceMdnsUpdateWrapper, true);
  timerAlarmWrite(mdnsUpdateTimer, mdnsUpdateInterval * clockFrequency / timerDivider, true);
  timerAlarmEnable(mdnsUpdateTimer);
}
