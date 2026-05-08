#ifndef FTRLAB_MOCK_DISCOVERY_SERVICE_PROVIDER_H
#define FTRLAB_MOCK_DISCOVERY_SERVICE_PROVIDER_H

#include <map>
#include <string>
#include "FTRLab/interfaces/IDiscoveryServiceProvider.hpp"

/**
 * Mock de IDiscoveryServiceProvider para testes unitários do Device.
 */
class MockDiscoveryServiceProvider : public IDiscoveryServiceProvider
{
public:
  bool beginCalled = false;
  bool endCalled = false;
  String lastHostname;

  // TXT records registrados: key → value
  std::map<std::string, std::string> txtRecords;

  bool begin(const char *hostname) override
  {
    beginCalled = true;
    lastHostname = hostname;
    return true;
  }

  void end() override { endCalled = true; }

  void addService(const char *, const char *, uint16_t) override {}

  void addServiceTxt(const char *, const char *, const char *key, const char *value) override
  {
    txtRecords[key] = value;
  }
};

#endif
