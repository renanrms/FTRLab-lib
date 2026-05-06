#include "FTRLab/Device.hpp"

unsigned int Device::sendMeasurementsBatch()
{
  String message = "\n{\"measurements\":[";
  String measurementString;
  unsigned measurementsAdded = 0;

  xSemaphoreTake(this->measurementsSemaphore, portMAX_DELAY);

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

  // Remove vírgula sobrando (só existe se ao menos uma medição foi adicionada) e fecha o payload
  if (measurementsAdded > 0)
    message = message.substring(0, message.length() - 1);
  message += "]}\n";

  this->networkProvider->clientPrint(message);
  return measurementsAdded;
}
