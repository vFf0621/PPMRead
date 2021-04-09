import serial, time
arduino = serial.Serial('COM7', 2000000)
while True:
    print(str(arduino.readline())[2:21])
    print(time.time())