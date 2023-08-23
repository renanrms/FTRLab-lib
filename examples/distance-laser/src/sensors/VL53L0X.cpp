#include "FTRLab.hpp"

#include "Adafruit_VL53L0X.h"

class VL53L0X : public Sensor
{
public:
  uint8_t triggerPin;
  uint8_t echoPin;
  Adafruit_VL53L0X lox = Adafruit_VL53L0X();

  VL53L0X(uint8_t triggerPin, uint8_t echoPin)
  {
    this->quantity = "distance";
    this->method = "Laser";

    Serial.println("Adafruit VL53L0X test");
    if (!lox.begin() ||
        !lox.configSensor(Adafruit_VL53L0X::VL53L0X_SENSE_HIGH_SPEED))
    {
      Serial.println(F("Failed to boot VL53L0X"));
      throw std::exception();
    }
  }

  String takeMeasure()
  {
    VL53L0X_RangingMeasurementData_t measure;

    lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

    if (measure.RangeStatus != 4)
    {
      // Serial.println("takeMeasure: " + String(measure.RangeMilliMeter));
      return String((double)measure.RangeMilliMeter / 1000.0, 5);
    }
    else
    {
      // Serial.println("fail: " + String(measure.RangeMilliMeter));
      throw std::exception();
    }
  }
};
