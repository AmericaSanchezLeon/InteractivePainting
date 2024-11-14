import serial, time
arduino = serial.Serial("/dev/cu.usbmodem14201", 9600)

while(arduino.is_open):

  print(arduino);
  time.sleep(3)
  arduino.write(b'3')
  #arduino.close()