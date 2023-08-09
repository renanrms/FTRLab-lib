#include "FTRLab/Board.hpp"

void communicationHandlerWrapper(void *pvParameters)
{
  board.communicationHandler();
}

TaskHandle_t communicationTask;

void measurementHandlerWrapper(void *pvParameters)
{
  board.measurementHandler();
}

TaskHandle_t measurementTask;

void Board::setup()
{
  Serial.begin(115200);

  this->printBoardInfo();

  xTaskCreatePinnedToCore(
      communicationHandlerWrapper,
      "COMM",
      1000,
      NULL,
      tskIDLE_PRIORITY,
      &communicationTask,
      0);

  xTaskCreatePinnedToCore(
      measurementHandlerWrapper,
      "MEAS",
      1000,
      NULL,
      configMAX_PRIORITIES,
      &measurementTask,
      1);
}
