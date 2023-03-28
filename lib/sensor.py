class Sensor:
  def __init__(self, module, ports):
    # TODO: adicionar kwargs para opções extras a serem passadas ao módulo
    self.module = module.Module(ports)
    self.isActive = True # False
    self.measurements = []

  def doMeasurement(self):
    # TODO: possivelmente adicionar mutex para evitar problema de concorrência se isso virar algo assíncrono
    self.measurements.append(self.module.measurement())
  
  def get(self):
    tmp = self.measurements.copy()
    self.measurements = []
    return tmp
