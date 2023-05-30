#include "FTRLab.hpp"

Board::Board()
{
  WiFi.macAddress().toCharArray(this->macAddress, MAC_ADDRESS_MAX_SIZE);
  this->getChipId().toCharArray(::chipId, CHIP_ID_MAX_SIZE);
}
