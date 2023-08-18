#include "FTRLab/Device.hpp"

void Device::sendMeasurements()
{
  unsigned long bytesSent = 0;

  if (!this->measurements.empty())
    bytesSent = this->sendMeasurementsBatch();
  else
    this->targetSendingPeriod++;

  Serial.println("Bytes sent: " + String(bytesSent) + "\t targetSendingPeriod: " + String(this->targetSendingPeriod));

  if (bytesSent < PAYLOAD_MAX_LENGTH / 2 && this->targetSendingPeriod < this->maximumSendingPeriod)
    this->targetSendingPeriod++;

  // Diminui período de envio se as medições estiverem se acumulando.
  if (!this->measurements.empty() &&
      (this->measurements.size() > 100 || // Prevenção de overflow
       this->measurements.front().timestamp - NTP.micros() / 1000000.0 >
           (this->maximumSendingPeriod / 2) / 1000.0)) // Garantia de tempo real
  {
    this->targetSendingPeriod *= 0.8;
  }
  else
  {
    this->targetSendingPeriod++;
  }

  if (this->targetSendingPeriod > this->maximumSendingPeriod)
    this->targetSendingPeriod = this->maximumSendingPeriod;
  else if (this->targetSendingPeriod < DEFAULT_MINIMUM_SENDING_PERIOD)
    this->targetSendingPeriod = DEFAULT_MINIMUM_SENDING_PERIOD;

  Serial.println("Updated targetSendingPeriod: " + String(this->targetSendingPeriod));
}
