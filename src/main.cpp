#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>

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

void printBoardAndNetworkInfo(WiFiClass);
String getChipId();
void IRAM_ATTR forceMdnsUpdate();

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

  printBoardAndNetworkInfo(WiFi);

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

  mdns_txt_item_t serviceTxtData[5] = {
      {"name", "Física Básica"},
      {"available", "true"},
      // Item opcional sobre bateria, presente apenas quando houver bateria.
      {"battery", "{\"level\":70,\"charging\":true}"},
      {"sensor", "{\"quantity\":\"distance\"}"},
      {"sensor", "{\"quantity\":\"temperature\"}"}};

  mdns_service_txt_set("_ftr-lab", "_tcp", serviceTxtData, 5);

  // Configura um timer para periodicamente setar o nome e forçar uma nova resposta MDNS.
  mdnsUpdateTimer = timerBegin(timers::mdnsUpdate, timerDivider, true);
  timerAttachInterrupt(mdnsUpdateTimer, &forceMdnsUpdate, true);
  timerAlarmWrite(mdnsUpdateTimer, mdnsUpdateInterval * clockFrequency / timerDivider, true);
  timerAlarmEnable(mdnsUpdateTimer);
}

void loop()
{
  delay(10000);
}

String getChipId()
{
  uint32_t chipIdAsNumber = 0;
  for (int i = 0; i < 17; i = i + 8)
  {
    chipIdAsNumber |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }

  return String(chipIdAsNumber);
}

void printBoardAndNetworkInfo(WiFiClass Wifi)
{
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Subnet Mask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("Broadcast: ");
  Serial.println(WiFi.broadcastIP());
  Serial.print("DNS 1: ");
  Serial.println(WiFi.dnsIP(0));
  Serial.print("DNS 2: ");
  Serial.println(WiFi.dnsIP(1));
}

void IRAM_ATTR forceMdnsUpdate()
{
  Serial.print("Configurando nome... ");
  MDNS.setInstanceName(chipId);
  Serial.println("ok");
}
