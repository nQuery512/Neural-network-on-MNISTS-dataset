#include <stdio.h>
#include <stdlib.h>
#include <opencv/cv.h>
#include <stdint.h>
#include <opencv/highgui.h>
#include "MNIST_parser.h"

IplImage* CreateImage(const CvArr* buf)
{
	IplImage* img = NULL;
	return img;
}

void displayImageSet(DATABASE* data, int nb_data)
{
	const char* windows_title = "MNIST dataset viewer";

	cvNamedWindow(windows_title, CV_WINDOW_AUTOSIZE);
	for(int i = 0; i < nb_data; i++)
	{ 
		//cvShowImage("windows_title", data[i]._data);
		//cvWaitKey(0);
	}
	//cvDestroyAllWindows();
  	//cvReleaseImage(&img);
}