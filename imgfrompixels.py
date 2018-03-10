import cv2
import sys
from pathlib import Path
import numpy as np

win = cv2.namedWindow('imgfrompixels', cv2.WINDOW_AUTOSIZE)
f = open('MNIST_neurones.txt', 'rb')
ret = 1
try:
	while ret == 1:
		float_img = np.random.random((28,28))
		im = np.array(float_img * 255, dtype = np.uint8)
		#threshed = cv2.adaptiveThreshold(im, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, 3, 0)
		im = cv2.resize(im,None,fx=10, fy=10, interpolation = cv2.INTER_CUBIC)
		cv2.imshow('imgfrompixels', im)
		cv2.waitKey(0)
except KeyboardInterrupt:
	cv2.destroyAllWindows()
	sys.exit("Succesfully exit")

