#include "FTRLab/Device.hpp"

void communicationTaskWrapper(void *pvParameters)
{
  device.communicationTask();
}

void measurementTaskWrapper(void *pvParameters)
{
  device.measurementTask();
}

void Device::setup()
{
  Serial.begin(115200);

  this->printDeviceInfo();

  // xTaskCreatePinnedToCore(
  //     communicationTaskWrapper,
  //     "COMM",
  //     10000,
  //     NULL,
  //     tskIDLE_PRIORITY,
  //     &this->communicationHandle,
  //     0);

  xTaskCreatePinnedToCore(
      measurementTaskWrapper,
      "MEAS",
      10000,
      NULL,
      configMAX_PRIORITIES,
      &this->measurementHandle,
      0);

  this->communicationTask();
  // this->measurementTask();
}
