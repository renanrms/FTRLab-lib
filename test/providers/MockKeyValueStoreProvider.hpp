#ifndef FTRLAB_MOCK_KEY_VALUE_STORE_PROVIDER_H
#define FTRLAB_MOCK_KEY_VALUE_STORE_PROVIDER_H

#include <map>
#include <string>
#include "FTRLab/interfaces/IKeyValueStoreProvider.hpp"

/**
 * Mock de IKeyValueStoreProvider para testes unitários do Device.
 * Usa um mapa em memória como armazenamento.
 */
class MockKeyValueStoreProvider : public IKeyValueStoreProvider
{
public:
  std::map<std::string, std::string> storage;

  bool isKey(const char *key) override
  {
    return storage.find(key) != storage.end();
  }

  String getString(const char *key, String defaultValue = String()) override
  {
    auto it = storage.find(key);
    return it != storage.end() ? String(it->second.c_str()) : defaultValue;
  }

  bool putString(const char *key, const char *value) override
  {
    storage[key] = value;
    return true;
  }
};

#endif
