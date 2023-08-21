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
  //     APP_CPU_NUM);

  xTaskCreatePinnedToCore(
      measurementTaskWrapper,
      "MEAS",
      10000,
      NULL,
      configMAX_PRIORITIES,
      &this->measurementHandle,
      PRO_CPU_NUM);

  this->communicationTask();
  // this->measurementTask();
}
