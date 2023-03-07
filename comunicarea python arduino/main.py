import serial

# Inițializează conexiunea serială cu Arduino
ser = serial.Serial('COM3', 1000000)

# Funcție pentru a trimite o comandă la Arduino
def send_command(command):
    ser.write(command.encode())

# Meniu pentru a alege motorul și comanda dorită
while True:
    print('1. Mișcă primul motor la poziția 512')
    print('2. Mișcă al doilea motor la poziția 512')
    print('3. Mișcă al treilea motor la poziția 512')
    choice = input('Alege o opțiune: ')

    # Trimite comanda la Arduino
    send_command(choice)

    #response = ser.readline().decode().strip()  # citim raspunsul de la Arduino
    #print(response)  # afisam raspunsul
