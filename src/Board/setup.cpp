#include "FTRLab/Board.hpp"

void Board::CommunicationHandler()
{
  int64_t lastSendingTime = NTP.micros();
  int64_t remainingTime;

  Serial.println("CommunicationTask running on core " + String(xPortGetCoreID()));

  while (true)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      digitalWrite(this->pins.networkLed, HIGH);

      if (this->client.connected())
      {
        remainingTime = this->measurementSendingPeriod - (NTP.micros() - lastSendingTime);
        Serial.println("Communication remainingTime = " + String(remainingTime));
        if (remainingTime > 0)
        {
          delayMicroseconds(remainingTime);
        }

        lastSendingTime = NTP.micros();
        this->sendAllMeasurements();
      }
      else
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
