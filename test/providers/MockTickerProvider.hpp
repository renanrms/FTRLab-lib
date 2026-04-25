#ifndef FTRLAB_MOCK_TICKER_PROVIDER_H
#define FTRLAB_MOCK_TICKER_PROVIDER_H

#include "FTRLab/interfaces/ITickerProvider.hpp"

/**
 * Mock de ITickerProvider para testes unitários do Device.
 * Armazena o callback e o argumento; permite disparo manual via tick().
 */
class MockTickerProvider : public ITickerProvider
{
public:
  bool attached = false;
  uint32_t intervalMs = 0;
  void (*callback)(void *) = nullptr;
  void *callbackArg = nullptr;

  void attach_ms(uint32_t milliseconds, void (*cb)(void *), void *arg) override
  {
    attached = true;
    intervalMs = milliseconds;
    callback = cb;
    callbackArg = arg;
  }

  void detach() override
  {
    attached = false;
    callback = nullptr;
    callbackArg = nullptr;
  }

  // Dispara o callback manualmente — útil para testar o comportamento do timer
  void tick()
  {
    if (attached && callback)
      callback(callbackArg);
  }
};

#endif
