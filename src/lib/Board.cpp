#include "FTR-Lab.hpp"

#include "time.h"
#include "getChipId.hpp"
#include "printNetworkInfo.hpp"

WiFiServer server = WiFiServer(3333);
WiFiClient client;

char chipId[CHIP_ID_MAX_SIZE];
hw_timer_t *mdnsUpdateTimer = NULL;

Board::Board(const char *name, const std::vector<Sensor *> sensors)
{
  this->name = name;
  this->sensors = sensors;
  WiFi.macAddress().toCharArray(this->macAddress, MAC_ADDRESS_MAX_SIZE);
  getChipId().toCharArray(::chipId, CHIP_ID_MAX_SIZE);

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

  printNetworkInfo(WiFi, ssid);

  // Setup MDNS
  setupMdns();

  server.begin(); // Inicia o servidor TCP na porta declarada no começo.
}

void Board::takeMeasurement(Sensor *sensor, unsigned index)
{
  time_t t1, t2, timestamp;

  time(&t1);
  String measure = sensor->takeMeasure();
  time(&t2);

  timestamp = (t1 + t2) / 2;

  this->measurements.push({index, timestamp, measure});
}

void Board::takeAllMeasurements()
{
  for (unsigned index = 0; index < this->sensors.size(); index++)
  {
    this->takeMeasurement(this->sensors[index], index);
  }
}

void Board::sendMeasurements()
{
  String menssage = "\n{\"measurements\":[";
  String measurementString;

  while (!this->measurements.empty() && menssage.length() < PAYLOAD_MAX_LENGTH - 3)
  {
    measurementString = String(this->measurements.front());

    if (menssage.length() + measurementString.length() <= PAYLOAD_MAX_LENGTH - 3)
    {
      menssage += measurementString;
      menssage += ",";
      this->measurements.pop();
    }
    else
    {
      // Se a medição sozinha excede o tamanho máximo possível, é descartada
      if (measurementString.length() > MEASUREMENT_MAX_LENGTH)
      {
        Serial.println("Error: measurement string exceded de maximum size.");
        this->measurements.pop();
      }
    }
  }

  // Retira vírgula sobrando ao final e finaliza mensagem
  menssage = menssage.substring(0, menssage.length() - 1);
  menssage += "]}\n";

  client.print(menssage);
  Serial.println(menssage);
}

void Board::setupMdns()
{
  if (!MDNS.begin(::chipId))
  {
    Serial.println("Error setting up MDNS responder!");
    while (1)
    {
      delay(1000);
    }
  }

  MDNS.addService("_ftr-lab", "_tcp", 3333);
  updateMdnsServiceTxtData();

  // TODO: printar informações do serviço e dos records TXT generalizados.

  Serial.println("\nServiço MDS adicionado");
  Serial.println("Nome: _ftr-lab");
  Serial.println("Protocolo: _tcp");
  Serial.println("Porta: 3333");

  // Configura um timer para periodicamente setar o nome e forçar uma nova resposta MDNS.
  mdnsUpdateTimer = timerBegin(timers::mdnsUpdate, timerDivider, true);
  timerAttachInterrupt(mdnsUpdateTimer, &forceMdnsUpdate, true);
  timerAlarmWrite(mdnsUpdateTimer, mdnsUpdateInterval * clockFrequency / timerDivider, true);
  timerAlarmEnable(mdnsUpdateTimer);
}

void Board::loop()
{
  this->tcp(); // Funçao que gerencia os pacotes e clientes TCP.
  if (client.connected())
  {
    this->takeAllMeasurements();
    this->sendMeasurements();
  }
  delay(1000);
}

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
    client = server.available(); // Disponabiliza o servidor para o cliente se conectar.
    delay(1);
  }
}

void Board::updateMdnsServiceTxtData()
{
  MDNS.addServiceTxt("_ftr-lab", "_tcp", "name", this->name);
  MDNS.addServiceTxt("_ftr-lab", "_tcp", "available", client.connected() ? "false" : "true");
  MDNS.addServiceTxt("_ftr-lab", "_tcp", "battery", this->batteryInfo);

  for (unsigned index = 0; index < this->sensors.size(); index++)
  {
    MDNS.addServiceTxt("_ftr-lab", "_tcp", "sensor[" + String(index) + "]", "{\"index\":" + String(index) + ",\"quantity\":\"" + this->sensors[index]->quantity + "\"}");
  }
}

void IRAM_ATTR forceMdnsUpdate()
{
  Serial.print("Configurando nome... ");
  MDNS.setInstanceName(chipId);
  Serial.println("ok");
}
