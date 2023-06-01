import cv2
import numpy as np
import matplotlib.pyplot as plt

# Citirea imaginii binare
im_bw = cv2.imread('poza_binary.jpg', cv2.IMREAD_GRAYSCALE)

# Detectarea liniilor utilizând transformata Hough
lines = cv2.HoughLines(im_bw, 5, np.pi/180, threshold=100)

# Creează o figură și un ax pentru afișare
fig, ax = plt.subplots()

# Afișează imaginea binară
ax.imshow(im_bw, cmap='gray')

# Extrage seturile de coordonate de început și sfârșit ale liniilor
line_coordinates = []
for line in lines:
    rho, theta = line[0]
    a = np.cos(theta)
    b = np.sin(theta)
    x0 = a * rho
    y0 = b * rho
    x1 = int(x0 + 100 * (-b))
    y1 = int(y0 + 100 * (a))
    x2 = int(x0 - 100 * (-b))
    y2 = int(y0 - 100 * (a))
    line_coordinates.append(((x1, y1), (x2, y2)))

# Afișează coordonatele liniilor
for line in line_coordinates:
    (x1, y1), (x2, y2) = line
    print(f"Linie: ({x1}, {y1}) - ({x2}, {y2})")

# Setează limita axei la dimensiunea imaginii
ax.set_xlim([0, im_bw.shape[1]])
ax.set_ylim([im_bw.shape[0], 0])

# Afișează axa cu liniile
plt.show()