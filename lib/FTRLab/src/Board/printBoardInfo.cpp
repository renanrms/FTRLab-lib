#include "FTRLab/Board.hpp"

void Board::printBoardInfo()
{
  Serial.println("\n===== FTRLab device infos =====");
  Serial.println("Id: " + this->chipId);
  Serial.println("Name: " + this->name);
  Serial.println("Sensors:");

  for (unsigned index = 0; index < this->sensors.size(); index++)
  {
    Serial.println(String(index) + "\t" + this->sensors[index]->quantity + "\t" + this->sensors[index]->method);
  }

  Serial.println();
}
