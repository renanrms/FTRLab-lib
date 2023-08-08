#include "FTRLab/Board.hpp"

void Board::loop()
{
  TickType_t xLastWakeTime = xTaskGetTickCount();
  BaseType_t xWasDelayed;

  while (true)
  {
    while (this->client.connected())
    {
      xWasDelayed = xTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(this->targetTakeingPeriod));
      this->takeAllMeasurements();
    }
    delay(100);
  }
}
