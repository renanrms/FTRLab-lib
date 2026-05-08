#ifndef FTRLAB_BOARDS_ESP32_GPIO_PROVIDER_H
#define FTRLAB_BOARDS_ESP32_GPIO_PROVIDER_H

#include <Arduino.h>
#include "FTRLab/interfaces/IGpioProvider.hpp"

/**
 * Implementação de IGpioProvider para ESP32.
 *
 * Usa as funções reais do Arduino para manipulação de GPIO.
 */
class ESP32GpioProvider : public IGpioProvider
{
public:
  ESP32GpioProvider() {}

  void pinMode(uint8_t pin, uint8_t mode) override { ::pinMode(pin, mode); }
  void digitalWrite(uint8_t pin, uint8_t value) override { ::digitalWrite(pin, value); }
  int digitalRead(uint8_t pin) override { return ::digitalRead(pin); }
};

#endif
