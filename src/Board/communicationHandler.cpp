#include "FTRLab/Board.hpp"

void Board::communicationHandler()
{
  bool clientConnected = false;

  Serial.println("Communication task running on core " + String(xPortGetCoreID()));

  while (true)
  {
    if (clientConnected != bool(this->client.connected()))
    {
      clientConnected = bool(this->client.connected());
      // this->updateMdnsServiceTxtData();
    }

    if (WiFi.status() != WL_CONNECTED)
    {
      digitalWrite(this->pins.networkLed, LOW);
      this->connectToNetwork();
      digitalWrite(this->pins.networkLed, HIGH);

      this->printNetworkInfo();
      this->setupNTP();
      this->server.begin();
      this->setupMdns();
    }
    else if (!this->client.connected())
    {
      this->client = this->server.available(); // Disponibiliza o servidor para o cliente se conectar.
    }

    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (WiFi.status() == WL_CONNECTED && this->client.connected())
    {
      BaseType_t xWasDelayed = xTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(this->targetSendingPeriod));
      this->sendAllMeasurements();
    }

    delay(100);
  }
}
