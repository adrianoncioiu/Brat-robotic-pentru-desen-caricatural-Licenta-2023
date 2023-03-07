import serial

ser = serial.Serial('COM3', 9600)  # deschidem comunicarea seriala cu Arduino
print("Conectare cu Arduino...")

while True:
    input_data = input("Introduceti 1 pentru aprinderea LED-ului sau 0 pentru starea LED-ului: ")
    ser.write(input_data.encode())  # trimitem datele la Arduino
    if input_data == '1' or input_data == '0':
        response = ser.readline().decode().strip()  # citim raspunsul de la Arduino
        print(response)  # afisam raspunsul
    else:
        print("Introduceti o valoare valida (0 sau 1)")
