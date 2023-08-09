#include "FTRLab/Board.hpp"

void Board::sendMeasurements()
{
  if (!this->measurements.empty())
    this->sendMeasurementsBatch();

  // Envia mais medições se estiverem se acumulando.
  while (!this->measurements.empty() &&
         (this->measurements.size() > 100 || // Prevenção de overflow
          this->measurements.front().timestamp - NTP.micros() / 1000000.0 >
              (this->targetSendingPeriod / 2) / 1000.0)) // Garantia de tempo real
  {
    delay(50); // Evita sobrecarregar o software desktop.
    this->sendMeasurementsBatch();
  }
}
