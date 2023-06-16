#include "FTRLab/Board.hpp"

void Board::loop()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    digitalWrite(this->pins.networkLed, HIGH);
  }
  else
  {
    digitalWrite(this->pins.networkLed, LOW);
    board.setup();
  }

  this->tcp();

  if (this->client.connected())
  {
    this->takeAllMeasurements();
    this->sendMeasurements();
  }

  delay(250);
}
