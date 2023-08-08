#include "FTRLab/Board.hpp"

void Board::CommunicationHandler()
{
  TickType_t xLastWakeTime = xTaskGetTickCount();
  BaseType_t xWasDelayed;

  Serial.println("Communication task running on core " + String(xPortGetCoreID()) + "\n");

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
      xWasDelayed = xTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(this->targetSendingPeriod));
      this->sendAllMeasurements();
    }
  }
}
