from machine import Pin
import network

# import esp
# esp.osdebug(None)

# import gc
# gc.collect()

# network.hostname('aaa.ftr-lab.local')

print('oi')

ssid = 'ITANET-CASTELO'
password = 'c45t310a2'

station = network.WLAN(network.STA_IF)

station.config(hostname='aaa.ftr-lab.local')
station.isActive(True)
station.connect(ssid, password)

while station.isconnected() == False:
  pass

print('Connection successful')
print(station.ifconfig())
