#include "FTRLab/internals/SemaphoreLock.hpp"

// TODO: Corrigir ou eliminar esta classe.

SemaphoreLock::SemaphoreLock(SemaphoreHandle_t sema) : semaphore(sema)
{
  this->hasLock = xSemaphoreTake(semaphore, portMAX_DELAY);
  while (hasLock != pdTRUE)
  {
    this->hasLock = xSemaphoreTake(semaphore, portMAX_DELAY);
  }
}

SemaphoreLock::~SemaphoreLock()
{
  while (this->hasLock == pdTRUE)
  {
    if (xSemaphoreGive(semaphore))
    {
      this->hasLock = pdFALSE;
    }
  }
}
