import serial



with open("test_com.txt", "rb") as file:
    data = file.read()

ser = serial.Serial("COM3", 9600)
ser.write(b"Serial data to be sent")

ser.write(data)

print(data)


ser.close()
