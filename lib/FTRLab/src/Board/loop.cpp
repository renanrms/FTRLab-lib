#include "FTRLab/Board.hpp"

void Board::loop()
{
  this->tcp(); // Funçao que gerencia os pacotes e clientes TCP.
  if (this->client.connected())
  {
    this->takeAllMeasurements();
    this->sendMeasurements();
  }
  delay(1000);
}
