#include "FTRLab/Board.hpp"

void Board::takeMeasurement(Sensor *sensor, unsigned index)
{
  int64_t t1, t2;
  double timestamp;

  try
  {
    t1 = NTP.micros();
    String measure = sensor->takeMeasure();
    t2 = NTP.micros();

    timestamp = ((double)(t1 + t2) / 2) / 1000000.0;

    // TODO: Resolver problema: se uma exceção for lançada entre o take e o give, a variável ficará travada para sempre.
    // Como o C++ tem exceções, é preciso tornar isso seguro alocando um objeto com destrutor que libera a trava
    // com seu destrutor. Ver se é melhor usar pthreads.
    xSemaphoreTake(this->measurementsQueue, portMAX_DELAY);
    this->measurements.push({index, timestamp, measure});
    xSemaphoreGive(this->measurementsQueue);
  }
  catch (std::exception error)
  {
    Serial.println("Measurement error from sensor " + String(index) + ".");
  }
}
