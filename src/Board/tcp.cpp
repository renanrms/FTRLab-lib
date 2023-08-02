#include "FTRLab/Board.hpp"

void Board::tcp()
{
  if (client.connected()) // Detecta se há clientes conectados no servidor.
  {
    if (client.available() > 0) // Verifica se o cliente conectado tem dados para serem lidos.
    {
      String req = "";
      while (client.available() > 0) // Armazena cada Byte (letra/char) na String para formar a mensagem recebida.
      {
        char z = client.read();
        req += z;
      }
      // Mostra a mensagem recebida do cliente no Serial Monitor.
      Serial.print("\nUm cliente enviou uma mensagem");
      Serial.print("\n...IP do cliente: ");
      Serial.print(client.remoteIP());
      Serial.print("\n...Mensagem do cliente: " + req + "\n");
      // Envia uma resposta para o cliente
      client.print("\nO servidor recebeu sua mensagem");
      client.print("\n...Seu IP: ");
      client.print(client.remoteIP());
      client.print("\n...Sua mensagem: " + req + "\n");
    }
  }
  else // Se nao houver cliente conectado,
  {
    client = server.available(); // Disponibiliza o servidor para o cliente se conectar.
    delay(1);
  }
}
