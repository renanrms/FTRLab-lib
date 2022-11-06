# import machine
from socket import socket, AF_INET, SOCK_STREAM
from json import dumps, loads

from .board import Board

board = Board()

HOST = ''              # Endereco IP do Servidor
PORT = 5000            # Porta que o Servidor esta

tcp = socket(AF_INET, SOCK_STREAM)
tcp.bind((HOST, PORT))
tcp.listen(1)

while True:
  con, cliente = tcp.accept()
  # Cria a tarefa pra lidar com a requisição
  print ('Concetado por', cliente)
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

