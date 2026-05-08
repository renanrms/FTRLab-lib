#ifndef FTRLAB_BOARDS_ESP32_TIME_PROVIDER_H
#define FTRLAB_BOARDS_ESP32_TIME_PROVIDER_H

#include <Arduino.h>
#include <ESPNtpClient.h>
#include "FTRLab/interfaces/ITimeProvider.hpp"

/**
 * Implementação de ITimeProvider para ESP32.
 * Delega para o objeto global NTP da biblioteca ESPNtpClient.
 *
 * O método micros() usa NTP.micros() que retorna um timestamp em
 * microssegundos sincronizado com a hora real via NTP.
 */
class ESP32TimeProvider : public ITimeProvider
{
public:
  void begin(const char *server) override { ::NTP.begin(server); }

  void stop() override { ::NTP.stop(); }

  int8_t syncStatus() override { return ::NTP.syncStatus(); }

  unsigned long getUptime() override { return ::NTP.getUptime(); }

  int64_t micros() override { return ::NTP.micros(); }

  String getTimeDateStringUs() override { return ::NTP.getTimeDateStringUs(); }
};

#endif
