#include "FTRLab/Board.hpp"

void Board::communicationTask()
{
  Serial.println("Communication task running on core " + String(xPortGetCoreID()));

  while (true)
  {
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

    while (WiFi.status() == WL_CONNECTED && !this->client.connected())
    {
      this->client = this->server.available(); // Disponibiliza o servidor para o cliente se conectar.
      delay(200);
    }

    if (this->client.connected())
    {
      Serial.println("Connection established to client " + this->client.remoteIP().toString() + ":" + String(this->client.remotePort()));
    }

    this->forceMdnsUpdate();

    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (WiFi.status() == WL_CONNECTED && this->client.connected())
    {
      BaseType_t xWasDelayed = xTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(this->targetSendingPeriod));
      this->sendMeasurements();
    }

    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("Connection to client ended.");
    }

    this->forceMdnsUpdate();
  }
}
