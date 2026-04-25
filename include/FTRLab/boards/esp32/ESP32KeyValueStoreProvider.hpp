#ifndef FTRLAB_BOARDS_ESP32_KEY_VALUE_STORE_PROVIDER_H
#define FTRLAB_BOARDS_ESP32_KEY_VALUE_STORE_PROVIDER_H

#include <Arduino.h>
#include <Preferences.h>
#include "FTRLab/interfaces/IKeyValueStoreProvider.hpp"

/**
 * Implementação de IKeyValueStoreProvider para ESP32.
 * Usa a biblioteca Preferences do ESP32 para armazenamento em flash.
 */
class ESP32KeyValueStoreProvider : public IKeyValueStoreProvider
{
public:
  bool isKey(const char *key) override { return prefs.isKey(key); }

  String getString(const char *key, String defaultValue = String()) override
  {
    return prefs.getString(key, defaultValue);
  }

  bool putString(const char *key, const char *value) override
  {
    return prefs.putString(key, value);
  }

private:
  ::Preferences prefs;
};

#endif
