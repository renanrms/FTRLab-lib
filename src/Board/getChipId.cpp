#include "FTRLab/Board.hpp"

String Board::getChipId()
{
  uint32_t chipIdAsNumber = 0;
  for (int i = 0; i < 17; i = i + 8)
  {
    chipIdAsNumber |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }

  return String(chipIdAsNumber);
}
