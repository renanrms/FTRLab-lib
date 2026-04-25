#ifndef FTRLAB_INTERFACE_TIME_PROVIDER_H
#define FTRLAB_INTERFACE_TIME_PROVIDER_H

#include <Arduino.h>

/**
 * Abstração de sincronização de tempo via NTP usado pelo Device.
 *
 * O método micros() é o mais crítico: retorna um timestamp em microssegundos
 * sincronizado com NTP, usado para marcar cada medição com precisão.
 */
class ITimeProvider
{
public:
  virtual ~ITimeProvider() = default;

  /* Inicia a sincronização NTP com o servidor indicado. */
  virtual void begin(const char *server) = 0;

  /* Encerra tentativas de sincronização (p.ex. sem acesso à internet). */
  virtual void stop() = 0;

  /* Retorna o status de sincronização: -1 = não sincronizado, >= 0 = ok. */
  virtual int8_t syncStatus() = 0;

  /* Retorna o uptime do dispositivo em segundos (usada no timeout de sync). */
  virtual unsigned long getUptime() = 0;

  /* Retorna o timestamp atual em microssegundos (sincronizado com NTP). */
  virtual int64_t micros() = 0;

  /* Retorna a data/hora atual como string formatada. */
  virtual String getTimeDateStringUs() = 0;
};

#endif
