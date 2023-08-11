#include "FTRLab/Board.hpp"

void communicationTaskWrapper(void *pvParameters)
{
  board.communicationTask();
}

void measurementTaskWrapper(void *pvParameters)
{
  board.measurementTask();
}

void Board::setup()
{
  Serial.begin(115200);

  this->printBoardInfo();

  xTaskCreatePinnedToCore(
      communicationTaskWrapper,
      "COMM",
      10000,
      NULL,
      tskIDLE_PRIORITY,
      &this->communicationHandle,
      0);

  xTaskCreatePinnedToCore(
      measurementTaskWrapper,
      "MEAS",
      10000,
      NULL,
      configMAX_PRIORITIES,
      &this->measurementHandle,
      1);
}
