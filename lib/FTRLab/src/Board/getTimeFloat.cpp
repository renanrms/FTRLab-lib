#include "FTRLab/Board.hpp"

#include <WiFiUdp.h>
#include <NTPClient.h>

float Board::getTimeFloat()
{
  unsigned long epochSeconds = this->timeClient->getEpochTime();
  unsigned long precisionTime = micros();
  unsigned long offset = epochSeconds - precisionTime / 1000000;

  return timeOffset + (static_cast<float>(precisionTime) / 1000000.0);
}
