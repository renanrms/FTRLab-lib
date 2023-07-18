#include "FTRLab.hpp"

const double SOUND_SPEED = 340;                  // Unit: m/s
const double MAXIMUM_MEASURABLE_DISTANCE = 5;    // Unit: m
const double MINIMUM_MEASURABLE_DISTANCE = 0.03; // Unit: m

class UltrasonicSensor : public Sensor
{
public:
  uint8_t triggerPin;
  uint8_t echoPin;

  UltrasonicSensor(uint8_t triggerPin, uint8_t echoPin)
  {
    this->quantity = "distance";
    this->method = "Ultrasônico";

    this->triggerPin = triggerPin;
    this->echoPin = echoPin;

    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
  }

  String takeMeasure()
  {
    // Gera o pulso a ser medido
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    // Obtém o tempo de duração do echo
    double duration = (double)pulseIn(echoPin, HIGH, 1000000 * MAXIMUM_MEASURABLE_DISTANCE / SOUND_SPEED);

    double measure = (duration / 2) * SOUND_SPEED / 1000000;

    if (measure < MINIMUM_MEASURABLE_DISTANCE || measure > MAXIMUM_MEASURABLE_DISTANCE)
      throw std::exception();

    // Retorna medida com 3 casas decimais (resolução de mm)
    return String(measure, 3);
  }
};
