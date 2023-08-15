#include "FTRLab.hpp"

const double SOUND_SPEED = 343;                  // Unit: m/s
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
    this->method = "Ultrassônico";

    this->triggerPin = triggerPin;
    this->echoPin = echoPin;

    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
  }

  String takeMeasure()
  {
    double result = 0;
    unsigned count = 0;

    for (unsigned i = 0; i < 6; i++)
    {

      // Gera o pulso a ser medido
      digitalWrite(triggerPin, LOW);
      delayMicroseconds(2);
      digitalWrite(triggerPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(triggerPin, LOW);

      // Obtém o tempo de duração do echo
      double duration = (double)pulseIn(echoPin, HIGH, 1000000 * 2 * MAXIMUM_MEASURABLE_DISTANCE / SOUND_SPEED);

      double measure = (duration / 2) * SOUND_SPEED / 1000000;

      if (measure < MINIMUM_MEASURABLE_DISTANCE || measure > MAXIMUM_MEASURABLE_DISTANCE)
      {
      }
      else
      {
        result += measure;
        count++;
      }
    }

    Serial.println(count);

    if (count > 0)
      return String(result / count, 5);
    else
      throw std::exception();
  }
};
