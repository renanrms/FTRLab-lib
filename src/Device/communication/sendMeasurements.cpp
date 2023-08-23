#include "FTRLab/Device.hpp"

unsigned int Device::sendMeasurements()
{
  unsigned long measurementsSent = 0;
  unsigned long accumulator = 0;

  /**
   * Envia medições se houverem e continua enviando se a quantidade de medições
   * acumuladas/novas na fila for maior do que se conseguiu enviar em um envio.
   */
  while (this->measurements.size() > measurementsSent)
  {
    measurementsSent = this->sendMeasurementsBatch();
    accumulator += measurementsSent;
  }

  return accumulator;
}
