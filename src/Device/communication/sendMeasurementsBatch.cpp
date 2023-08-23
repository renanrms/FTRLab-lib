#include "FTRLab/Device.hpp"
#include "FTRLab/internals/SemaphoreLock.hpp"

unsigned int Device::sendMeasurementsBatch()
{
  String message = "\n{\"measurements\":[";
  String measurementString;
  unsigned measurementsAdded = 0;

  // SemaphoreLock lock = SemaphoreLock(this->measurementsSemaphore);
  while (xSemaphoreTake(this->measurementsSemaphore, portMAX_DELAY) != pdTRUE)
  {
    delay(10);
  }

  while (!this->measurements.empty() && message.length() < PAYLOAD_MAX_LENGTH - 3)
  {
    measurementString = String(this->measurements.front());

    if (message.length() + measurementString.length() <= PAYLOAD_MAX_LENGTH - 3)
    {
      // Se a medição cabe na string, é adicionada.
      message += measurementString;
      message += ",";
      this->measurements.pop();
      measurementsAdded++;
    }
    else if (measurementsAdded == 0)
    {
      // Se a medição sozinha não cabe na string, é descartada.
      Serial.println("Error: measurement string exceeded de maximum size.\n" +
                     String(this->measurements.front()));
      this->measurements.pop();
    }
    else
    {
      // Se a medição não pode ser adicionada à string atual, é mantida para ser enviada no próximo ciclo.
      break;
    }
  }

  // lock.~SemaphoreLock();
  xSemaphoreGive(this->measurementsSemaphore);

  // Retira vírgula sobrando ao final e finaliza mensagem
  message = message.substring(0, message.length() - 1);
  message += "]}\n";

  client.print(message);
  // Serial.println(message);
  return measurementsAdded;
}
