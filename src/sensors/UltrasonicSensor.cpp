#include "FTRLab.hpp"

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
    double duration = (double)pulseIn(echoPin, HIGH, 5000000);

    double measure = (duration / 2) * 0.00034;

    return String(measure);
  }
};
