#include "FTRLab/Device.hpp"

unsigned int Device::sendMeasurementsBatch()
{
  String message = "\n{\"measurements\":[";
  String measurementString;
  unsigned measurementsAdded = 0;

  while (xSemaphoreTake(this->measurementsSemaphore, portMAX_DELAY) != pdTRUE)
  {
    delay(10);
  }

  while (!this->measurements.empty() && message.length() < PAYLOAD_MAX_LENGTH - 3)
  {
    measurementString = String(this->measurements.front());

    if (message.length() + measurementString.length() <= PAYLOAD_MAX_LENGTH - 3)
    {
      message += measurementString;
      message += ",";
      this->measurements.pop();
      measurementsAdded++;
    }
    else if (measurementsAdded == 0)
    {
      Serial.println("Error: measurement string exceeded de maximum size.\n" +
                     String(this->measurements.front()));
      this->measurements.pop();
    }
    else
    {
      break;
    }
  }

  xSemaphoreGive(this->measurementsSemaphore);

  // Remove vírgula sobrando e fecha o payload
  message = message.substring(0, message.length() - 1);
  message += "]}\n";

  this->networkProvider->clientPrint(message);
  return measurementsAdded;
}
