#ifndef FTRLAB_MOCK_GPIO_PROVIDER_H
#define FTRLAB_MOCK_GPIO_PROVIDER_H

#include <map>
#include "FTRLab/interfaces/IGpioProvider.hpp"

/**
 * Mock de IGpioProvider para testes unitários do Device.
 * Armazena o estado dos pinos em memória para verificação nos testes.
 */
class MockGpioProvider : public IGpioProvider
{
public:
  std::map<uint8_t, uint8_t> pinValues;
  std::map<uint8_t, uint8_t> pinModes;

  void pinMode(uint8_t pin, uint8_t mode) override { pinModes[pin] = mode; }

  void digitalWrite(uint8_t pin, uint8_t value) override { pinValues[pin] = value; }

  int digitalRead(uint8_t pin) override
  {
    auto it = pinValues.find(pin);
    return it != pinValues.end() ? it->second : LOW;
  }
};

#endif
