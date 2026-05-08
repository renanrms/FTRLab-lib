#ifndef FTRLAB_INTERFACE_NETWORK_PROVIDER_H
#define FTRLAB_INTERFACE_NETWORK_PROVIDER_H

#include <Arduino.h>

/**
 * Abstração de conectividade WiFi e servidor TCP usados pelo Device.
 *
 * Cada instância gerencia internamente a conexão WiFi, o servidor TCP
 * e o cliente TCP ativo. O Device interage apenas através desta interface.
 */
class INetworkProvider
{
public:
  virtual ~INetworkProvider() = default;

  // ── Conexão WiFi ─────────────────────────────────────────────────────────

  /* Retorna true se a conexão WiFi está estabelecida. */
  virtual bool isConnected() = 0;

  /* Inicia conexão a uma rede WiFi. Retorna o status resultante. */
  virtual int begin(const char *ssid, const char *password) = 0;

  /* Aguarda o resultado da tentativa de conexão. */
  virtual int waitForConnectResult() = 0;

  /* Inicia o provisionamento via EspTouch SmartConfig. */
  virtual void startSmartConfig() = 0;

  /* Verifica se o provisionamento SmartConfig foi concluído. */
  virtual bool smartConfigDone() = 0;

  /* Retorna o SSID da rede conectada (ou recém-provisionada). */
  virtual String SSID() = 0;

  /* Retorna a senha da rede (disponível após SmartConfig). */
  virtual String psk() = 0;

  /* Retorna o endereço MAC do dispositivo. */
  virtual String macAddress() = 0;

  /* Retorna o endereço IP local. */
  virtual String localIP() = 0;

  /* Retorna a máscara de sub-rede. */
  virtual String subnetMask() = 0;

  /* Retorna o gateway. */
  virtual String gatewayIP() = 0;

  /* Retorna o endereço de broadcast. */
  virtual String broadcastIP() = 0;

  /* Retorna o servidor DNS (dns_no = 0 ou 1). */
  virtual String dnsIP(uint8_t dns_no = 0) = 0;

  // ── Servidor / cliente TCP ───────────────────────────────────────────────

  /* Inicia o servidor TCP na porta configurada. */
  virtual void serverBegin() = 0;

  /* Aceita um cliente pendente (chamado em loop até connectar). */
  virtual void acceptClient() = 0;

  /* Retorna true se há um cliente TCP ativo conectado. */
  virtual bool clientConnected() = 0;

  /* Retorna o IP remoto do cliente ativo. */
  virtual String clientRemoteIP() = 0;

  /* Retorna a porta remota do cliente ativo. */
  virtual uint16_t clientRemotePort() = 0;

  /* Envia uma string ao cliente ativo. */
  virtual size_t clientPrint(const String &s) = 0;
};

#endif
