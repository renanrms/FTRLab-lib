#ifndef FTRLAB_INTERFACE_GPIO_PROVIDER_H
#define FTRLAB_INTERFACE_GPIO_PROVIDER_H

#include <Arduino.h>

/**
 * Interface para provedores de GPIO.
 *
 * Abstração para permitir injeção de dependência de funcionalidades de manipulação
 * de pinos GPIO, possibilitando testes unitários.
 */
class IGpioProvider
{
public:
  virtual ~IGpioProvider() = default;

  virtual void pinMode(uint8_t pin, uint8_t mode) = 0;
  virtual void digitalWrite(uint8_t pin, uint8_t value) = 0;
  virtual int digitalRead(uint8_t pin) = 0;
};

#endif
