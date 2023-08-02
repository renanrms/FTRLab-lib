#include "FTRLab/Board.hpp"

void Board::setupNTP()
{
  NTP.begin("pool.ntp.org", false);

  Serial.println("\nSynchronizing device clock with NTP. Timeout is " + String(NTP_SYNC_WAIT_TIME) + "s");

  time_t NtpSyncStart = NTP.getUptime();
  while (NTP.syncStatus() == -1 && NTP.getUptime() - NtpSyncStart < NTP_SYNC_WAIT_TIME)
  {
    digitalWrite(this->pins.networkLed, HIGH);
    delay(1950);
    digitalWrite(this->pins.networkLed, LOW);
    delay(50);
  }

  if (NTP.syncStatus() != -1)
  {
    this->timeSynced = true;
    Serial.println("First sync done.");
  }
  else
  {
    // Para as tentativas de sincronização para não gerar descontinuidade nas medidas.
    NTP.stop();
    Serial.println("NTP response not received. It's possible the network don't have access to internet.");
    Serial.println("Will continue without global time configured.");
  }
  Serial.println(String("Time: ") + NTP.getTimeDateStringUs());
}
