#ifndef FTRLAB_INTERFACE_KEY_VALUE_STORE_PROVIDER_H
#define FTRLAB_INTERFACE_KEY_VALUE_STORE_PROVIDER_H

#include <Arduino.h>

/**
 * Abstração de armazenamento chave-valor persistente usado pelo Device
 * para guardar credenciais WiFi entre reinicializações.
 */
class IKeyValueStoreProvider
{
public:
  virtual ~IKeyValueStoreProvider() = default;

  /* Retorna true se a chave existe no armazenamento. */
  virtual bool isKey(const char *key) = 0;

  /* Retorna o valor String associado à chave, ou defaultValue se ausente. */
  virtual String getString(const char *key, String defaultValue = String()) = 0;

  /* Persiste um valor String. Retorna true em caso de sucesso. */
  virtual bool putString(const char *key, const char *value) = 0;
};

#endif
