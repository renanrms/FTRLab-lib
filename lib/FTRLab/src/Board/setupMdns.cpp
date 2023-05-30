#include "FTRLab.hpp"

void Board::setupMdns()
{
  if (!MDNS.begin(::chipId))
  {
    Serial.println("Error setting up MDNS responder!");
    while (1)
    {
      delay(1000);
    }
  }

  MDNS.addService("_ftr-lab", "_tcp", 3333);
  updateMdnsServiceTxtData();

  // TODO: printar informações do serviço e dos records TXT generalizados.

  Serial.println("\nServiço MDS adicionado");
  Serial.println("Nome: _ftr-lab");
  Serial.println("Protocolo: _tcp");
  Serial.println("Porta: 3333");

  // Configura um timer para periodicamente setar o nome e forçar uma nova resposta MDNS.
  mdnsUpdateTimer = timerBegin(timers::mdnsUpdate, timerDivider, true);
  timerAttachInterrupt(mdnsUpdateTimer, &forceMdnsUpdate, true);
  timerAlarmWrite(mdnsUpdateTimer, mdnsUpdateInterval * clockFrequency / timerDivider, true);
  timerAlarmEnable(mdnsUpdateTimer);
}
