#ifndef FTRLAB_INTERFACE_TICKER_PROVIDER_H
#define FTRLAB_INTERFACE_TICKER_PROVIDER_H

#include <Arduino.h>

/**
 * Abstração de temporizador periódico usado pelo Device para disparar
 * atualizações forçadas de mDNS em intervalo regular.
 *
 * O callback recebe um argumento void* para que o chamador possa passar
 * um ponteiro para o próprio Device sem depender de variável global.
 */
class ITickerProvider
{
public:
  virtual ~ITickerProvider() = default;

  /* Agenda a execução periódica de callback(arg) a cada milliseconds ms. */
  virtual void attach_ms(uint32_t milliseconds, void (*callback)(void *), void *arg) = 0;

  /* Cancela o temporizador. */
  virtual void detach() = 0;
};

#endif
