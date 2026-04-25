#include "FTRLab/Device.hpp"

void Device::setDevicePins(uint8_t networkButton, uint8_t networkLed)
{
  this->pins.networkButton = networkButton;
  this->pins.networkLed = networkLed;

  this->gpioProvider->pinMode(this->pins.networkButton, INPUT_PULLUP);
  this->gpioProvider->pinMode(this->pins.networkLed, OUTPUT);
}
