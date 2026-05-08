#ifndef FTRLAB_BOARDS_ESP32_TICKER_PROVIDER_H
#define FTRLAB_BOARDS_ESP32_TICKER_PROVIDER_H

#include <Arduino.h>
#include <Ticker.h>
#include "FTRLab/interfaces/ITickerProvider.hpp"

/**
 * Implementação de ITickerProvider para ESP32.
 * Usa a biblioteca Ticker do Arduino/ESP32.
 */
class ESP32TickerProvider : public ITickerProvider
{
public:
  void attach_ms(uint32_t milliseconds, void (*callback)(void *), void *arg) override
  {
    ticker.attach_ms<void *>(milliseconds, callback, arg);
  }

  void detach() override { ticker.detach(); }

private:
  ::Ticker ticker;
};

#endif
