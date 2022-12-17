import cv2
from PIL import Image
import numpy as np

poza = cv2.imread('blabla.jpg', 1)
#poza = cv2.VideoCapture(0)

img_half = cv2.resize(poza, (500, 500), fx=0.5, fy=0.5)
cv2.imshow('Resized_img', img_half)
cv2.waitKey(1000)

im_gray = cv2.cvtColor(img_half, cv2.COLOR_RGB2GRAY)
cv2.imshow('Grayscale', im_gray)
cv2.waitKey(1000)

(thresh, im_bw) = cv2.threshold(im_gray, 35, 255, cv2.THRESH_BINARY)
#im_bw //= 255

cv2.imshow('binary_img', im_bw)
cv2.imwrite('poza_binary.jpg', im_bw)
cv2.waitKey(4000)

im = Image.open('poza_binary.jpg')
pixels = list(im.getdata())
print(pixels)