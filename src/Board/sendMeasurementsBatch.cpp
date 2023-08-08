#include "FTRLab/Board.hpp"

void Board::sendMeasurementsBatch()
{
  String message = "\n{\"measurements\":[";
  String measurementString;

  while (!this->measurements.empty() && message.length() < PAYLOAD_MAX_LENGTH - 3)
  {
    Serial.println("message.length() = " + String(message.length()));

    measurementString = String(this->measurements.front());

    if (message.length() + measurementString.length() <= PAYLOAD_MAX_LENGTH - 3)
    {
      // Se a medição cabe na string, é adicionada.
      message += measurementString;
      message += ",";
      this->measurements.pop();
    }
    else if (measurementString.length() > MEASUREMENT_MAX_LENGTH)
    {
      // Se a medição sozinha excede o tamanho máximo possível, é descartada.
      Serial.println("Error: measurement string exceeded de maximum size.");
      this->measurements.pop();
    }
    else
    {
      // Se a medição não pode ser adicionada à string atual, é mantida para ser enviada no próximo ciclo.
      break;
    }
  }

  // Retira vírgula sobrando ao final e finaliza mensagem
  message = message.substring(0, message.length() - 1);
  message += "]}\n";

  Serial.println("Sent: message.length() = " + String(message.length()));

  client.print(message);
  // Serial.println(message);
}
