#ifndef FTRLAB_INTERFACE_DISCOVERY_SERVICE_PROVIDER_H
#define FTRLAB_INTERFACE_DISCOVERY_SERVICE_PROVIDER_H

#include <Arduino.h>

/**
 * Abstração do serviço mDNS usado pelo Device para anunciar-se na rede local.
 */
class IDiscoveryServiceProvider
{
public:
  virtual ~IDiscoveryServiceProvider() = default;

  /* Inicializa o responder mDNS com o hostname indicado. */
  virtual bool begin(const char *hostname) = 0;

  /* Encerra o responder mDNS. */
  virtual void end() = 0;

  /* Anuncia um serviço na rede. */
  virtual void addService(const char *service, const char *proto, uint16_t port) = 0;

  /* Adiciona ou atualiza um registro TXT no serviço anunciado. */
  virtual void addServiceTxt(const char *service, const char *proto, const char *key, const char *value) = 0;
};

#endif
