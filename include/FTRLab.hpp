#ifndef FTRLAB_H
#define FTRLAB_H "FTRLAB_H"

#include <Arduino.h>

#include "FTRLab/Sensor.hpp"
#include "FTRLab/Device.hpp"

/**
 * Instância de dispositivo FTRLab disponível globalmente.
 *
 * Utilize as propriedades e os métodos públicos para controlar o funcionamento do dispositivo.
 * Crie e adicione sensores.
 *
 * Para instruções mais detalhadas veja exemplos da biblioteca em:
 * https://registry.platformio.org/libraries/renanrms/FTRLab/examples
 */
extern Device &device;

#endif
