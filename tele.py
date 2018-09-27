import serial
import time
import sys
def sendData(input):
  ser.write(input + '\r\n')
  outstr = ''
  time.sleep(1.1)
  while ser.inWaiting() > 0:
    outstr += ser.read(1)

  if outstr != '':
    print outstr


def read():
  while True:
    outstr = ''
    
    while ser.inWaiting() > 0:
      outstr += ser.readline(1)
      #for str in outstr:
      #  sys.stdout.write(hex(ord(str)))
      #print "--"
      if outstr != '':
        sys.stdout.write( outstr)
        sys.stdout.flush()
        outstr = ''



ser = serial.Serial(
    port='/dev/ttyUSB0',
    baudrate=9600,
    parity=serial.PARITY_ODD,
    stopbits=serial.STOPBITS_TWO,
    bytesize=serial.SEVENBITS
)
print "start"
read()
#ser.isOpen()
#sendData("+++")
#sendData("ATI")



