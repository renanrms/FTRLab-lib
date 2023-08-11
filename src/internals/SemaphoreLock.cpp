#include "FTRLab/internals/SemaphoreLock.hpp"

SemaphoreLock::SemaphoreLock(SemaphoreHandle_t sema) : semaphore(sema)
{
  xSemaphoreTake(semaphore, portMAX_DELAY);
}

SemaphoreLock::~SemaphoreLock()
{
  xSemaphoreGive(semaphore);
}
