#include "FTRLab/Board.hpp"

void Board::setupNTP()
{
  NTP.begin("pool.ntp.org", false);

  Serial.print("\nSynchronizing device clock with NTP ");

  // NTPStatus_t possible values:
  // syncd = 0       -> Time synchronized correctly
  // unsyncd = -1    -> Time may not be valid
  // partialSync = 1 -> NPT is synchronised but precission is below threshold
  while (NTP.syncStatus() == -1)
  {
    digitalWrite(this->pins.networkLed, HIGH);
    delay(950);
    digitalWrite(this->pins.networkLed, LOW);
    delay(50);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("First sync done.");
  Serial.println(String("Time: ") + NTP.getTimeDateStringUs());
}
