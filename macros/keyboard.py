import serial
import subprocess

arduino = serial.Serial(port='COM8', baudrate=9600, timeout=.1)

app_a = ""
app_b = ""
app_c = ""
app_d = ""
app_e = ""
app_f = ""


while True:
    data = arduino.readline().decode('utf-8')
    if (len(data) > 0 and last != data) :
        last = data
        print(data)
        if (data == 'a'):
            subprocess.Popen(app_a)
        elif (data == 'b'):
            subprocess.Popen(app_b)
        elif (data == 'c'):
            subprocess.Popen(app_c)
        elif (data == 'd'):
            subprocess.Popen(app_d)
        elif (data == 'e'):
            subprocess.Popen(app_e)
        elif (data == 'f'):
            subprocess.Popen(app_f)