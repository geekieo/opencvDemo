// Eroding_and_Dilating.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <stdio.h>
#include <cv.h>
#include <highgui.h>
#include <cvaux.h> //��������ͷ�ļ�

int main(int argc, char** argv)
{
	IplImage *img = cvLoadImage("4un-zishiying.jpg", 0);
	if (img == NULL)
	{
		printf("img load failed!\n");
		return 0;
	}
	IplImage *img_erode = cvCreateImage(cvGetSize(img), 8, 1);
	IplImage *img_dilate = cvCreate+Image(cvGetSize(img), 8, 1);

	cvErode(img, img_erode, NULL, 1); //��ʴ
	cvDilate(img, img_dilate, NULL, 1); //����

	cvNamedWindow("img_erode");
	cvNamedWindow("img_dilate");

	cvShowImage("img_erode", img_erode);
	cvShowImage("img_dilate", img_dilate);

	cvWaitKey(-1);


	cvReleaseImage(&img_dilate);
	cvReleaseImage(&img_erode);

	cvDestroyAllWindows();


	return 0;
}