#include "FTRLab/Device.hpp"

void Device::setupNTP()
{
  this->timeProvider->begin("pool.ntp.org");

  Serial.println("\nSynchronizing device clock with NTP. Timeout is " + String((long)NTP_SYNC_WAIT_TIME) + "s");

  time_t syncStart = this->timeProvider->getUptime();
  while (this->timeProvider->syncStatus() == -1 &&
         this->timeProvider->getUptime() - syncStart < NTP_SYNC_WAIT_TIME)
  {
    this->gpioProvider->digitalWrite(this->pins.networkLed, LOW);
    delay(50);
    this->gpioProvider->digitalWrite(this->pins.networkLed, HIGH);
    delay(1950);
  }

  if (this->timeProvider->syncStatus() != -1)
  {
    this->timeSynced = true;
    Serial.println("\nFirst time sync done.");
  }
  else
  {
    this->timeProvider->stop();
    Serial.println("NTP response not received. Will continue without global time configured.");
  }

  Serial.println(String("Time: ") + this->timeProvider->getTimeDateStringUs());

  this->gpioProvider->digitalWrite(this->pins.networkLed, HIGH);
}
