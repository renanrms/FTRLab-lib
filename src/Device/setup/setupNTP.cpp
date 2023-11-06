#include "FTRLab/Device.hpp"

void NtpEventLogger(NTPEvent_t event)
{
  Serial.println("[NTP] " + String(NTP.ntpEvent2str(event)));
}

void Device::setupNTP()
{
  NTP.onNTPSyncEvent(&NtpEventLogger);
  NTP.begin("pool.ntp.org", false);

  Serial.println("\nSynchronizing device clock with NTP. Timeout is " + String(NTP_SYNC_WAIT_TIME) + "s");
  Serial.println("NPT server name: " + String(NTP.getNtpServerName()));
  Serial.println("NPT sync interval for normal operation: " + String(NTP.getLongInterval()) + "s");
  Serial.println("NPT sync interval while nor synced : " + String(NTP.getShortInterval()) + "s\n");

  time_t NtpSyncStart = NTP.getUptime();
  while (NTP.syncStatus() == -1 && NTP.getUptime() - NtpSyncStart < NTP_SYNC_WAIT_TIME)
  {
    digitalWrite(this->pins.networkLed, LOW);
    delay(50);
    digitalWrite(this->pins.networkLed, HIGH);
    delay(1950);
  }

  if (NTP.syncStatus() != -1)
  {
    this->timeSynced = true;
    Serial.println("\nFirst time sync done.");
  }
  else
  {
    // Para as tentativas de sincronização para não gerar descontinuidade nas medidas.
    NTP.stop();
    Serial.println("NTP response not received. It's possible the network don't have access to internet.");
    Serial.println("Will continue without global time configured.");
  }
  Serial.println(String("Time: ") + NTP.getTimeDateStringUs());

  digitalWrite(this->pins.networkLed, HIGH);
}
