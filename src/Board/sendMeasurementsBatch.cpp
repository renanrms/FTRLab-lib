#include "FTRLab/Board.hpp"

void Board::sendMeasurementsBatch()
{
  String message = "\n{\"measurements\":[";
  String measurementString;
  unsigned measurementsAdded = 0;

  xSemaphoreTake(this->measurementsQueue, portMAX_DELAY);

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
      Serial.println("Error: measurement string exceeded de maximum size.");
      this->measurements.pop();
    }
    else
    {
      // Se a medição não pode ser adicionada à string atual, é mantida para ser enviada no próximo ciclo.
      break;
    }
  }

  xSemaphoreGive(this->measurementsQueue);

  // Retira vírgula sobrando ao final e finaliza mensagem
  message = message.substring(0, message.length() - 1);
  message += "]}\n";

  client.print(message);
  // Serial.println(message);
}
