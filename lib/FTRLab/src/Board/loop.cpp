#include <WiFi.h>

#include "FTRLab/Board.hpp"

extern WiFiClient client;

void Board::loop()
{
  this->tcp(); // Funçao que gerencia os pacotes e clientes TCP.
  if (client.connected())
  {
    this->takeAllMeasurements();
    this->sendMeasurements();
  }
  delay(1000);
}
