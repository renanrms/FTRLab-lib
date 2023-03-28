# import machine
from socket import socket, AF_INET, SOCK_STREAM
from json import dumps, loads

# from lib.board import Board
class Sensor:
  def __init__(self, module, ports):
    # TODO: adicionar kwargs para opções extras a serem passadas ao módulo
    self.module = module(ports)
    self.isActive = True # False
    self.measurements = []

  def doMeasurement(self):
    # TODO: possivelmente adicionar mutex para evitar problema de concorrência se isso virar algo assíncrono
    self.measurements.append(self.module.measurement())
  
  def get(self):
    tmp = self.measurements.copy()
    self.measurements = []
    return tmp

class hc_sr04:
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


board = Board()

HOST = ''
PORT = 5000

tcp = socket(AF_INET, SOCK_STREAM)
tcp.bind((HOST, PORT))
tcp.listen(1)

while True:
  con, cliente = tcp.accept()
  # Cria a tarefa pra lidar com a requisição
  print ('Conectado por', cliente)
  while True:
    # Receber mensagem da aplicação
    # TODO: Se estiver desconectado tem que sair do loop pra aceitar nova conexão
    msg = con.recv(1024)
    # Processa a mensagem recebida se houver, aplicando configurações ou respondendo
    if msg:
      msg = loads(msg)
      print(msg)
    # Faz a medida dos sensores que estiverem ativos
    board.doAllMeasurements()
    # Envia os dados
    results = board.getAllMeasurements()
    print(results)
    con.send(dumps(results))

