#ifndef FTRLAB_SENSOR_H
#define FTRLAB_SENSOR_H "FTRLAB_SENSOR_H"

class Sensor
{
public:
  String name;
  String quantity;

  virtual String takeMeasure() = 0;

private:
};

#endif
