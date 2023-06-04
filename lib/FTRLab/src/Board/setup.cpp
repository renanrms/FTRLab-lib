#include "FTRLab/Board.hpp"

void Board::setup()
{
  Serial.begin(115200);

  this->printBoardInfo();

  // Função: connectToNetwork
  WiFi.begin(this->wifiSsid.c_str(), this->password.c_str());
  Serial.print("Connecting to " + wifiSsid);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");

  this->printNetworkInfo();

  // Setup MDNS
  setupMdns();

  this->server.begin(); // Inicia o servidor TCP na porta declarada no começo.
}
