#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <queue>
#include "time.h"
#include "getChipId.hpp"
#include "printNetworkInfo.hpp"

typedef struct
{
  time_t timestamp;
  String measure;
  operator String() const
  {
    return String("{\"sensorIndex\":\"0\",\"timestamp\":") + String(timestamp) + String(",\"value\":") + measure + String("}");
  }
} measurement;

#define MAC_ADDRESS_BUF_SIZE 18
#define CHIP_ID_BUF_SIZE 11

const uint16_t timerDivider = 80;
const unsigned clockFrequency = 800000000;
enum timers
{
  mdnsUpdate
};
const unsigned mdnsUpdateInterval = 30;
hw_timer_t *mdnsUpdateTimer = NULL;

const char *ssid = "ITANET-CASTELO";
const char *password = "c45t310a2";
char macAddress[MAC_ADDRESS_BUF_SIZE];
char chipId[CHIP_ID_BUF_SIZE];
WiFiServer sv(3333); // Cria o objeto servidor na porta 555
WiFiClient cl;       // Cria o objeto cliente.
std::queue<measurement> measurements;

void IRAM_ATTR forceMdnsUpdate();
void tcp();
void getInternalHallMeasurement();
void sendData();

void setup()
{
  Serial.begin(115200);

  WiFi.macAddress().toCharArray(macAddress, MAC_ADDRESS_BUF_SIZE);
  getChipId().toCharArray(chipId, CHIP_ID_BUF_SIZE);
  Serial.printf("\nChip Id: %s\n", chipId);

  WiFi.begin(ssid, password);
  Serial.printf("Connecting to %s ", ssid);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");

  printNetworkInfo(WiFi, ssid);

  if (!MDNS.begin(chipId))
  {
    Serial.println("Error setting up MDNS responder!");
    while (1)
    {
      delay(1000);
    }
  }

  MDNS.addService("_ftr-lab", "_tcp", 3333);
  Serial.println("\nServiço MDS adicionado");
  Serial.println("Nome: _ftr-lab");
  Serial.println("Protocolo: _tcp");
  Serial.println("Porta: 3333");

  mdns_txt_item_t serviceTxtData[6] = {
      {"name", "Física Básica"},
      {"available", "true"},
      // Item opcional sobre bateria, presente apenas quando houver bateria.
      {"battery", "{\"level\":70,\"charging\":true}"},
      {"sensor", "{\"index\":\"0\",\"quantity\":\"hall\"}"},
      {"sensor", "{\"index\":\"1\",\"quantity\":\"distance\"}"},
      {"sensor", "{\"index\":\"2\",\"quantity\":\"temperature\"}"}};

  mdns_service_txt_set("_ftr-lab", "_tcp", serviceTxtData, 6);

  // Configura um timer para periodicamente setar o nome e forçar uma nova resposta MDNS.
  mdnsUpdateTimer = timerBegin(timers::mdnsUpdate, timerDivider, true);
  timerAttachInterrupt(mdnsUpdateTimer, &forceMdnsUpdate, true);
  timerAlarmWrite(mdnsUpdateTimer, mdnsUpdateInterval * clockFrequency / timerDivider, true);
  timerAlarmEnable(mdnsUpdateTimer);

  sv.begin(); // Inicia o servidor TCP na porta declarada no começo.
}

void loop()
{
  tcp(); // Funçao que gerencia os pacotes e clientes TCP.
  if (cl.connected())
  {
    getInternalHallMeasurement();
    sendData();
  }
  delay(1000);
}

void IRAM_ATTR forceMdnsUpdate()
{
  Serial.print("Configurando nome... ");
  MDNS.setInstanceName(chipId);
  Serial.println("ok");
}

void tcp()
{
  if (cl.connected()) // Detecta se há clientes conectados no servidor.
  {
    if (cl.available() > 0) // Verifica se o cliente conectado tem dados para serem lidos.
    {
      String req = "";
      while (cl.available() > 0) // Armazena cada Byte (letra/char) na String para formar a mensagem recebida.
      {
        char z = cl.read();
        req += z;
      }
      // Mostra a mensagem recebida do cliente no Serial Monitor.
      Serial.print("\nUm cliente enviou uma mensagem");
      Serial.print("\n...IP do cliente: ");
      Serial.print(cl.remoteIP());
      Serial.print("\n...Mensagem do cliente: " + req + "\n");
      // Envia uma resposta para o cliente
      cl.print("\nO servidor recebeu sua mensagem");
      cl.print("\n...Seu IP: ");
      cl.print(cl.remoteIP());
      cl.print("\n...Sua mensagem: " + req + "\n");
    }
  }
  else // Se nao houver cliente conectado,
  {
    cl = sv.available(); // Disponabiliza o servidor para o cliente se conectar.
    delay(1);
  }
}

void sendData()
{
  String menssage = "\n{\"measurements\":[";
  String measurementString;

  while (!measurements.empty() && menssage.length() < 500)
  {
    measurementString = String(measurements.front());
    if (measurementString.length() + menssage.length() > 500)
      continue;
    menssage += measurementString;
    menssage += ",";
    measurements.pop();
  }

  menssage = menssage.substring(0, menssage.length() - 1);
  menssage += "]}\n";

  cl.print(menssage);
  Serial.println(menssage);
}

void getInternalHallMeasurement()
{
  time_t t1, t2, timestamp;

  time(&t1);
  String measure = String(hallRead());
  time(&t2);

  timestamp = (t1 + t2) / 2;

  measurements.push({timestamp, measure});
}

// unsigned long getTime() {
//   time_t now;
//   struct tm timeinfo;
//   if (!getLocalTime(&timeinfo)) {
//     //Serial.println("Failed to obtain time");
//     return(0);
//   }
//   time(&now);
//   return now;
// }
