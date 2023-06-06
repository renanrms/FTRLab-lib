#ifndef FTRLAB_SENSOR_H
#define FTRLAB_SENSOR_H "FTRLAB_SENSOR_H"

class Sensor
{
public:
  String quantity;
  String method;

  virtual String takeMeasure() = 0;

private:
};

#endif
