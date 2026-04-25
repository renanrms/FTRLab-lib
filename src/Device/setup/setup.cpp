#include "FTRLab/Device.hpp"

static void communicationTaskWrapper(void *pvParameters)
{
  static_cast<Device *>(pvParameters)->communicationTask();
}

static void measurementTaskWrapper(void *pvParameters)
{
  static_cast<Device *>(pvParameters)->measurementTask();
}

void Device::setup()
{
  this->gpioProvider->digitalWrite(this->pins.networkLed, LOW);

  Serial.begin(115200);

  this->printDeviceInfo();

  xTaskCreatePinnedToCore(
      communicationTaskWrapper,
      "COMM",
      10000,
      this,
      tskIDLE_PRIORITY,
      &this->communicationHandle,
      PRO_CPU_NUM);

  this->measurementTask();
}
