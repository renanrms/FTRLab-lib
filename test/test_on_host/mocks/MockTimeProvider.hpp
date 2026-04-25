#ifndef FTRLAB_MOCK_TIME_PROVIDER_H
#define FTRLAB_MOCK_TIME_PROVIDER_H

#include "FTRLab/interfaces/ITimeProvider.hpp"

/**
 * Mock de ITimeProvider para testes unitários do Device.
 *
 * micros() avança a cada chamada por stepUs, permitindo simular
 * a passagem de tempo de forma determinística.
 */
class MockTimeProvider : public ITimeProvider
{
public:
  int8_t syncStatus_ = -1;       // -1 = não sincronizado
  unsigned long uptime_ = 0;
  int64_t currentMicros_ = 0;
  int64_t stepUs = 1000;         // avanço por chamada a micros()
  String timeDateString = "2024-01-01 00:00:00";

  bool beginCalled = false;
  bool stopCalled = false;

  void begin(const char *) override { beginCalled = true; }

  void stop() override { stopCalled = true; }

  int8_t syncStatus() override { return syncStatus_; }

  unsigned long getUptime() override { return uptime_; }

  int64_t micros() override
  {
    currentMicros_ += stepUs;
    return currentMicros_;
  }

  String getTimeDateStringUs() override { return timeDateString; }
};

#endif
