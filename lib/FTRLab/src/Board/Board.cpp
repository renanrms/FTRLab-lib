#include <WiFi.h>

#include "FTRLab/Board.hpp"

extern char chipId[CHIP_ID_MAX_SIZE];

Board::Board()
{
  WiFi.macAddress().toCharArray(this->macAddress, MAC_ADDRESS_MAX_SIZE);
  this->getChipId().toCharArray(::chipId, CHIP_ID_MAX_SIZE);
}
