#include "FTRLab/Board.hpp"

void Board::sendMeasurements()
{
  String message = "\n{\"measurements\":[";
  String measurementString;

  while (!this->measurements.empty() && message.length() < PAYLOAD_MAX_LENGTH - 3)
  {
    measurementString = String(this->measurements.front());

    if (message.length() + measurementString.length() <= PAYLOAD_MAX_LENGTH - 3)
    {
      message += measurementString;
      message += ",";
      this->measurements.pop();
    }
    else
    {
      // Se a medição sozinha excede o tamanho máximo possível, é descartada
      if (measurementString.length() > MEASUREMENT_MAX_LENGTH)
      {
        Serial.println("Error: measurement string exceded de maximum size.");
        this->measurements.pop();
      }
    }
  }

  // Retira vírgula sobrando ao final e finaliza mensagem
  message = message.substring(0, message.length() - 1);
  message += "]}\n";

  client.print(message);
  Serial.println(message);
}
