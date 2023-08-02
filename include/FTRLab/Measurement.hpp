#ifndef FTRLAB_MEASUREMENT_H
#define FTRLAB_MEASUREMENT_H "FTRLAB_MEASUREMENT_H"

#include "constants.hpp"

typedef struct
{
  unsigned index;
  double timestamp;
  String measure;
  /// @brief Retorna a string da medição. Caso seu length exceda MEASUREMENT_MAX_LENGTH, pode ter sido truncado.
  operator String() const
  {
    char measurementString[MEASUREMENT_MAX_SIZE + 1];
    snprintf(measurementString, MEASUREMENT_MAX_SIZE + 1, "{\"sensorIndex\":\"%u\",\"timestamp\":%f,\"value\":%s}", index, timestamp, measure);
    return String(measurementString);
  }
} Measurement;

#endif
