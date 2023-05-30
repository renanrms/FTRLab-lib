#include "FTR-Lab.hpp"

void Board::setup()
{
  Serial.begin(115200);

  // Função: printBoardInfo
  Serial.printf("\nChip Id: %s\n", ::chipId);

  // Função: connectToNetwork
  WiFi.begin(this->ssid, this->password);
  Serial.printf("Connecting to %s ", ssid);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");

  this->printNetworkInfo();

  // Setup MDNS
  setupMdns();

  server.begin(); // Inicia o servidor TCP na porta declarada no começo.
}
