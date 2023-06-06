#include "FTRLab/Board.hpp"

Board::Board()
{
  this->macAddress = WiFi.macAddress();
  this->chipId = this->getChipId();

  WiFiUDP ntpUDP;
  this->timeClient = new NTPClient(ntpUDP, "pool.ntp.org");
}
