class Module:
  def __init__(self, ports):
    self.greatness = 'Distância'
    self.name = 'HC-SR04'
    try:
      self.ports = {
        'trigger': ports['trigger'],
        'echo': ports['echo']
      }
    except:
      raise Exception('Não foram fornecidas as portas necerrárias para o sensor.')
    # TODO: configurar as portas como entrada ou saída adequadamente.

  def masurement():
    # Retorna a medição usando o sensor com suas portas definidas
    return {'value': 1, 'time':0}
