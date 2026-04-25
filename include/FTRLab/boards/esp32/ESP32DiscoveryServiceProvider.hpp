#ifndef FTRLAB_BOARDS_ESP32_DISCOVERY_SERVICE_PROVIDER_H
#define FTRLAB_BOARDS_ESP32_DISCOVERY_SERVICE_PROVIDER_H

#include <Arduino.h>
#include <ESPmDNS.h>
#include "FTRLab/interfaces/IDiscoveryServiceProvider.hpp"

/**
 * Implementação de IDiscoveryServiceProvider para ESP32.
 * Delega para o objeto global MDNS da biblioteca ESPmDNS.
 */
class ESP32DiscoveryServiceProvider : public IDiscoveryServiceProvider
{
public:
  bool begin(const char *hostname) override { return ::MDNS.begin(hostname); }

  void end() override { ::MDNS.end(); }

  void addService(const char *service, const char *proto, uint16_t port) override
  {
    ::MDNS.addService(service, proto, port);
  }

  void addServiceTxt(const char *service, const char *proto, const char *key, const char *value) override
  {
    ::MDNS.addServiceTxt(service, proto, key, value);
  }
};

#endif
