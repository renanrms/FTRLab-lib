#include "FTRLab/Board.hpp"

void CommunicationHandlerWrapper(void *pvParameters)
{
  board.CommunicationHandler();
}

TaskHandle_t CommunicationTask;

void Board::setup()
{
  Serial.begin(115200);

  this->printBoardInfo();

  xTaskCreatePinnedToCore(
      CommunicationHandlerWrapper, /* Task function. */
      "Communication",             /* name of task. */
      10000,                       /* Stack size of task */
      NULL,                        /* parameter of the task */
      tskIDLE_PRIORITY,            /* priority of the task */
      &CommunicationTask,          /* Task handle to keep track of created task */
      0);                          /* pin task to core 0 */
}
