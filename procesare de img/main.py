import cv2
from PIL import Image
import numpy as np
import serial
import time

#ser = serial.Serial("/dev/ttyUSB0", 1000000, timeout=1)

#poza din fisier
poza = cv2.imread('blabla4.jpeg', 1)

#Poza facuta cu webcam
#image = cv2.VideoCapture(0)
#result, poza = image.read()
cv2.imshow('poza', poza)
cv2.waitKey(1000)

#dimensionare pentru spatiu de lucru
img_half = cv2.resize(poza, (120, 170), fx=0.5, fy=0.5)
cv2.imshow('Resized_img', img_half)
cv2.imwrite('poza_redim.jpg', img_half)
cv2.waitKey(1000)

#eroziune si dilatare imagine
img_erosion = cv2.erode(img_half, (100, 100), iterations=6)
cv2.imshow('Erosion', img_erosion)
cv2.imwrite('poza_erodata.jpg', img_erosion)
cv2.waitKey(1000)
img_dilation = cv2.dilate(img_erosion, (100, 100), iterations=2)
cv2.imshow('Dilation', img_dilation)
cv2.imwrite('poza_dilatata.jpg', img_dilation)
cv2.waitKey(1000)

#blur imagine pentru a diminua zgomotele
img_blur = cv2.GaussianBlur(img_dilation, (5, 5), 0)
cv2.imshow('Blur', img_blur)
cv2.imwrite('poza_blur.jpg', img_blur)
cv2.waitKey(1000)

#culori monocrome imagine pentru a diminua zgomotele
im_gray = cv2.cvtColor(img_blur, cv2.COLOR_RGB2GRAY)
cv2.imshow('Grayscale', im_gray)
cv2.imwrite('poza_gri.jpg', im_gray)
cv2.waitKey(1000)

#transormare imagine binara
(thresh, im_bw) = cv2.threshold(im_gray, 45, 255, cv2.THRESH_BINARY)
#im_bw //= 255

cv2.imshow('binary_img', im_bw)
cv2.imwrite('poza_binary.jpg', im_bw)
cv2.waitKey(4000)


im = Image.open('poza_binary.jpg')
pixels = list(im.getdata())

ini = open("initial.txt", "w")
f = open("results.txt", "w")


j = 0
lin = 0
col = 0
mat = [[0 for _ in range(171)] for _ in range(121)]

for i in pixels:
    if i < 50:
        i = 1
    else:
        i = 0
    f.write("%s " % i)
#adaug valori in matrice

    j += 1
    lin = int(j / 170)
    col = j % 120
    if col == 120:
        col = 0
        lin += 1
        f.write("\n")
    mat[lin][col] = i

'''
#unde 1 trimit pe seriala
for i in range(120):
    for j in range(170):
        f.write("%d " % mat[i][j])

        if mat[i][j]==1:

            #data = str (i/1000) + ',' + str (j/1000+0.1) + '\n'
            data = str(round(i / 1000, 3)) + ',' + str(round(j / 1000 + 0.1, 3)) + '\n'

            #ser.write(data.encode())
            #time.sleep(1)
            f.write(data)

    f.write("\n")




    #pentru linii
'''
'''
for i in range(121):
    x1 = 0
    y1 = 0
    x2 = 0
    y2 = 0
    for j in range(171):
        if mat[i][j] == 1:
            if x1 == 0 and y1 == 0:
                x1 = i
                y1 = j
            else:
                x2 = i
                y2 = j
        if mat[i][j] == 0 and x1 != 0 and y1 != 0 and x2 != 0 and y2 != 0:
            print(x1, y1, "-", x2, y2, "\n")
            ini.write("%s " % x1)
            ini.write("%s " % y1)
            ini.write("%s " % x2)
            ini.write("%s " % y2)
            ini.write("\n")
            x1 = 0
            y1 = 0
            x2 = 0
            y2 = 0
'''