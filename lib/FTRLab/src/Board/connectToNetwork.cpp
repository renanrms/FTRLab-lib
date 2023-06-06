#include "FTRLab/Board.hpp"

void Board::connectToNetwork()
{
  WiFi.begin(this->ssid.c_str(), this->password.c_str());
  Serial.print("Connecting to " + ssid);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
}
