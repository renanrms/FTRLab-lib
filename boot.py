from machine import Pin
from network import WLAN, STA_IF

# import esp
# esp.osdebug(None)

# import gc
# gc.collect()

ssid = 'estrelinha'
password = '12345678'

station = WLAN(STA_IF)

station.isActive(True)
station.connect(ssid, password)

while station.isconnected() == False:
  pass

print('Connection successful')
print(station.ifconfig())

# 