#include "FTRLab/Board.hpp"

void Board::CommunicationHandler()
{
  TickType_t xLastWakeTime = xTaskGetTickCount();
  BaseType_t xWasDelayed;

  Serial.println("CommunicationTask running on core " + String(xPortGetCoreID()));

  while (true)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      digitalWrite(this->pins.networkLed, HIGH);

      if (!this->client.connected())
      {
        this->client = this->server.available(); // Disponibiliza o servidor para o cliente se conectar.
        delay(100);
      }
    }
    else
    {
      digitalWrite(this->pins.networkLed, LOW);

      this->connectToNetwork();
      this->printNetworkInfo();
      this->setupNTP();
      this->server.begin();
      this->setupMdns();
    }

    while (WiFi.status() == WL_CONNECTED && this->client.connected())
    {
      xWasDelayed = xTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(this->measurementSendingPeriod));
      this->sendAllMeasurements();
    }
  }
}

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
      "CommunicationTask",         /* name of task. */
      10000,                       /* Stack size of task */
      NULL,                        /* parameter of the task */
      tskIDLE_PRIORITY,            /* priority of the task */
      &CommunicationTask,          /* Task handle to keep track of created task */
      0);                          /* pin task to core 0 */
}
