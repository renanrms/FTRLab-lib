#include "FTRLab/Board.hpp"

void IRAM_ATTR forceMdnsUpdateWrapper()
{
  board.forceMdnsUpdate();
}

void Board::setupMdns()
{
  if (!MDNS.begin(this->chipId))
  {
    Serial.println("Error setting up MDNS responder!");
    while (1)
    {
      delay(1000);
    }
  }

  MDNS.addService(MDNS_SERVICE_NAME, "_tcp", PORT);
  updateMdnsServiceTxtData();

  // TODO: printar informações do serviço e dos records TXT generalizados.

  Serial.println("\nServiço MDS adicionado");
  Serial.println("Nome: " + MDNS_SERVICE_NAME);
  Serial.println("Protocolo: _tcp");
  Serial.println("Porta: " + String(PORT));

  // Configura um timer para periodicamente setar o nome e forçar uma nova resposta MDNS.
  mdnsUpdateTimer = timerBegin(timers::mdnsUpdate, timerDivider, true);
  timerAttachInterrupt(mdnsUpdateTimer, &forceMdnsUpdateWrapper, true);
  timerAlarmWrite(mdnsUpdateTimer, mdnsUpdateInterval * clockFrequency / timerDivider, true);
  timerAlarmEnable(mdnsUpdateTimer);
}
