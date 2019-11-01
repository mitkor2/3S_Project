import numpy as np
import cv2

im = cv2.imread('Pic/pic1.jpg')
imgray = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)
ret, thresh = cv2.threshold(imgray, 127, 255, 0)
im2, contours, hierarchy = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
cnt = contours[4]
cv2.drawContours(im, [cnt], 0, (0,255,0), 3)
print(im.shape)
cv2.imshow('image', im2)
#To save the picture in some path
path='Pic/'
cv2.imwrite(str(path)+ 'mask1.jpg',im2)
cv2.waitKey(0)
cv2.destroyAllWindows()

