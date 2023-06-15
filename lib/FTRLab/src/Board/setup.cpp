#include "FTRLab/Board.hpp"

void Board::setup()
{
  Serial.begin(115200);

  // Configura os pinos da placa
  pinMode(5, INPUT_PULLUP);
  pinMode(18, OUTPUT);

  this->printBoardInfo();

  this->connectToNetwork();

  this->printNetworkInfo();

  this->setupNTP();

  this->server.begin();

  this->setupMdns();
}
