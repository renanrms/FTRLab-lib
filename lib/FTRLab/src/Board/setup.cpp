#include "FTRLab/Board.hpp"

void Board::setup()
{
  Serial.begin(115200);

  this->printBoardInfo();

  this->connectToNetwork();

  this->printNetworkInfo();

  this->setupNTP();

  this->server.begin();

  this->setupMdns();
}
