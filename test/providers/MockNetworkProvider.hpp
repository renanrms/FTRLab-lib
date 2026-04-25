#ifndef FTRLAB_MOCK_NETWORK_PROVIDER_H
#define FTRLAB_MOCK_NETWORK_PROVIDER_H

#include "FTRLab/interfaces/INetworkProvider.hpp"

/**
 * Mock de INetworkProvider para testes unitários do Device.
 *
 * Permite configurar previamente os retornos e depois verificar
 * quais métodos foram chamados e com quais argumentos.
 */
class MockNetworkProvider : public INetworkProvider
{
public:
  // ── Estado configurável ───────────────────────────────────────────────────
  int wifiStatus = WL_DISCONNECTED;
  bool smartConfigDone_ = false;
  String ssid_ = "";
  String psk_ = "";
  String mac_ = "AA:BB:CC:DD:EE:FF";
  String localIP_ = "192.168.1.100";
  String subnetMask_ = "255.255.255.0";
  String gatewayIP_ = "192.168.1.1";
  String broadcastIP_ = "192.168.1.255";
  String dnsIP_ = "8.8.8.8";
  bool clientConnected_ = false;
  String clientIP_ = "192.168.1.200";
  uint16_t clientPort_ = 12345;

  // ── Registro de chamadas ──────────────────────────────────────────────────
  bool beginCalled = false;
  String beginSsid;
  String beginPassword;
  bool serverBeginCalled = false;
  bool acceptClientCalled = false;
  String lastPrinted;

  // ── Implementação ─────────────────────────────────────────────────────────
  int status() override { return wifiStatus; }

  int begin(const char *ssid, const char *password) override
  {
    beginCalled = true;
    beginSsid = ssid;
    beginPassword = password;
    return wifiStatus;
  }

  int waitForConnectResult() override { return wifiStatus; }
  void mode(int) override {}
  bool beginSmartConfig() override { return true; }
  bool smartConfigDone() override { return smartConfigDone_; }
  String SSID() override { return ssid_; }
  String psk() override { return psk_; }
  String macAddress() override { return mac_; }
  String localIP() override { return localIP_; }
  String subnetMask() override { return subnetMask_; }
  String gatewayIP() override { return gatewayIP_; }
  String broadcastIP() override { return broadcastIP_; }
  String dnsIP(uint8_t = 0) override { return dnsIP_; }

  void serverBegin() override { serverBeginCalled = true; }

  void acceptClient() override { acceptClientCalled = true; }

  bool clientConnected() override { return clientConnected_; }

  String clientRemoteIP() override { return clientIP_; }

  uint16_t clientRemotePort() override { return clientPort_; }

  size_t clientPrint(const String &s) override
  {
    lastPrinted = s;
    return s.length();
  }
};

#endif
