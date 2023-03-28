from lib.sensor import Sensor

import hc_sr04

class Board:
  def __init__(self):
    self.name = 'Mecânica'
    self.sensors = [
      Sensor(hc_sr04, {'trigger': 1, 'echo':2})
    ]

  def doAllMeasurements(self):
    for sensor in self.sensors:
      if sensor.isActive:
        sensor.doMasurement()

  def getAllMeasurements(self):
    results = {}
    for index, sensor in enumerate(self.sensors):
      if sensor.isActive:
        results[index] = sensor.get()
