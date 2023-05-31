#include "FTRLab/Board.hpp"

#include <WiFi.h>
extern WiFiClient client;

void Board::sendMeasurements()
{
  String menssage = "\n{\"measurements\":[";
  String measurementString;

  while (!this->measurements.empty() && menssage.length() < PAYLOAD_MAX_LENGTH - 3)
  {
    measurementString = String(this->measurements.front());

    if (menssage.length() + measurementString.length() <= PAYLOAD_MAX_LENGTH - 3)
    {
      menssage += measurementString;
      menssage += ",";
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
  menssage = menssage.substring(0, menssage.length() - 1);
  menssage += "]}\n";

  client.print(menssage);
  Serial.println(menssage);
}
