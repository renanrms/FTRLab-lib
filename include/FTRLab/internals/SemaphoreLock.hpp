#ifndef FTRLAB_SEMAPHORE_LOCK_H
#define FTRLAB_SEMAPHORE_LOCK_H "FTRLAB_SEMAPHORE_LOCK_H"

#include <Arduino.h>
#include <freertos/semphr.h>

class SemaphoreLock
{
public:
  SemaphoreLock(SemaphoreHandle_t sema);
  ~SemaphoreLock();

private:
  SemaphoreHandle_t semaphore;
  BaseType_t hasLock = pdFALSE;
};

#endif
