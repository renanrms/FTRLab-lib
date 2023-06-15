#include "FTRLab/Board.hpp"

void Board::loop()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    digitalWrite(18, HIGH);
  }
  else
  {
    digitalWrite(18, LOW);
    board.setup();
  }

  this->tcp();

  if (this->client.connected())
  {
    this->takeAllMeasurements();
    this->sendMeasurements();
  }

  delay(200);
}
