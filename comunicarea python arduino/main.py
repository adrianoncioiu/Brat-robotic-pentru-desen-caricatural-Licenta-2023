import serial

ser = serial.Serial('COM3', 1000000)  # deschidem comunicarea seriala cu Arduino
print("Conectare cu Arduino...")

while True:
    input_data = input("Introduceti 1 pentru aprinderea LED-ului sau 0 pentru starea LED-ului: ")
    ser.write(input_data.encode())  # trimitem datele la Arduino
    #response = ser.readline().decode().strip()  # citim raspunsul de la Arduino
    #print(response)  # afisam raspunsul
else:
    print("Introduceti o valoare valida (0 sau 1)")
11