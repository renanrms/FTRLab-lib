#include "FTRLab/Board.hpp"

Board::Board()
{
  WiFi.macAddress().toCharArray(this->macAddress, MAC_ADDRESS_MAX_SIZE);
  this->getChipId().toCharArray(this->chipId, CHIP_ID_MAX_SIZE);
}
