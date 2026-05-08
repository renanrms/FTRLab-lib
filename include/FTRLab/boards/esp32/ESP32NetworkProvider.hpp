#ifndef FTRLAB_BOARDS_ESP32_NETWORK_PROVIDER_H
#define FTRLAB_BOARDS_ESP32_NETWORK_PROVIDER_H

#include <Arduino.h>
#include <WiFi.h>
#include "FTRLab/interfaces/INetworkProvider.hpp"
#include "FTRLab/constants.hpp"

/**
 * Implementação de INetworkProvider para ESP32.
 * Encapsula o WiFi global do Arduino e gerencia o servidor/cliente TCP.
 */
class ESP32NetworkProvider : public INetworkProvider
{
public:
  ESP32NetworkProvider() : server(PORT) {}

  // ── Conexão WiFi ─────────────────────────────────────────────────────────

  bool isConnected() override { return ::WiFi.status() == WL_CONNECTED; }

  int begin(const char *ssid, const char *password) override
  {
    return ::WiFi.begin(ssid, password);
  }

  int waitForConnectResult() override { return ::WiFi.waitForConnectResult(); }

  void startSmartConfig() override
  {
    ::WiFi.mode(WIFI_AP_STA);
    ::WiFi.beginSmartConfig();
  }

  bool smartConfigDone() override { return ::WiFi.smartConfigDone(); }

  String SSID() override { return ::WiFi.SSID(); }

  String psk() override { return ::WiFi.psk(); }

  String macAddress() override { return ::WiFi.macAddress(); }

  String localIP() override { return ::WiFi.localIP().toString(); }

  String subnetMask() override { return ::WiFi.subnetMask().toString(); }

  String gatewayIP() override { return ::WiFi.gatewayIP().toString(); }

  String broadcastIP() override { return ::WiFi.broadcastIP().toString(); }

  String dnsIP(uint8_t dns_no = 0) override { return ::WiFi.dnsIP(dns_no).toString(); }

  // ── Servidor / cliente TCP ───────────────────────────────────────────────

  void serverBegin() override { server.begin(); }

  void acceptClient() override { client = server.available(); }

  bool clientConnected() override { return client.connected(); }

  String clientRemoteIP() override { return client.remoteIP().toString(); }

  uint16_t clientRemotePort() override { return client.remotePort(); }

  size_t clientPrint(const String &s) override
  {
    return client.write((const uint8_t *)s.c_str(), s.length());
  }

private:
  ::WiFiServer server;
  ::WiFiClient client;
};

#endif
