import cv2
import sys
import numpy as np

#Initialisation
SIZE = 28*28
NB_NEURONES = int((sys.argv[1]))
inp = open('MNIST_neurones.txt', 'rb')
label = open('MNIST_labels.txt', 'rb');
i = 0
y = 0
t = 0
str2 = 'label: '

while y < NB_NEURONES:
	#Lecture fichier
	array = []
	i = 0

	while i < SIZE:
		pixels = inp.read(1)
		array.append(pixels[0])
		i = i + 1
	
	y = 0
	print(t, end='\t')
	t = t + 1

	for lettre in array:
		if y%2 == 0:
			print(' ', end='')
		y = y + 1
		print("%02X" % lettre, end='')	

	y = 0
	print('___________________')
	im = np.array(array, dtype = np.uint8)
	#Image carrée
	im.shape = (28, 28)
	#Augmentation de la taille de l'image 
	im = cv2.resize(im,None,fx=10, fy=10, interpolation = cv2.INTER_CUBIC)
	#Affichage image
	str1 = "neurone "
	res = str1+ str(t-1)
	letter = label.read(1)
	print("%02X" % letter[0])
	cv2.putText(im, str2 + str(letter[0]), (195,270), cv2.FONT_HERSHEY_SIMPLEX, 0.7, 255, 2)
	cv2.putText(im, res, (0,270), cv2.FONT_HERSHEY_SIMPLEX, 0.7, 255, 2)
	cv2.imshow('MNIST viewer', im)
	#Attente entrée clavier
	key = cv2.waitKey(0)
	i = 0
	y = y + 1
inp.close()
label.close()
