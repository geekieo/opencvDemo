// cvAdaptiveThresholdExample.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


/************cvAdaptiveThreshold Example************/

#include "highgui.h"
#include "cv.h"
#include <stdlib.h>
#include <stdio.h>

char wnd1[] = "in";
char wnd2[] = "out";

//读取trackbar上的两个值,实际两参数计算在on_track里
int _blocksize = 0;
int _param1 = 0;

IplImage *pImg = NULL;    //源图像
IplImage *pGray = NULL;   //灰度图
IplImage *pOut = NULL;    //二值图轮廓；

void on_track(int position);  //trackbar回调函数

int main(int argc, char **argv)
{
	cvNamedWindow(wnd1, 1);
	cvNamedWindow(wnd2, 1);

	pImg = cvLoadImage("4ul2.bmp");
	pGray = cvCreateImage(cvGetSize(pImg), IPL_DEPTH_8U, 1);
	pOut = cvCreateImage(cvGetSize(pImg), IPL_DEPTH_8U, 1);
	cvCvtColor(pImg, pGray, CV_RGB2GRAY);

	//创建两个滑动条
	cvCreateTrackbar("blocksize", wnd2, &_blocksize, 50, on_track);
	cvCreateTrackbar("param1", wnd2, &_param1, 100, on_track);

	cvShowImage(wnd1, pImg);
	cvWaitKey(0);

	cvReleaseImage(&pImg);
	cvReleaseImage(&pOut);
	cvReleaseImage(&pGray);
	cvDestroyWindow(wnd1);
	cvDestroyWindow(wnd2);

	return 0;
}

void on_track(int position)
{
	int blocksize = _blocksize * 2 + 3;     //计算阈值的像素邻域大小3,5,7...
	int param1 = _param1 - 50;    //被均值和加权均值减去的常量, 范围取[-50,50]

	cvAdaptiveThreshold(pGray,
		pOut,
		255,
		CV_ADAPTIVE_THRESH_MEAN_C,
		CV_THRESH_BINARY, blocksize, param1
		);
	printf("blocksize: %d, param1: %d\n", blocksize, param1);
	cvShowImage(wnd2, pOut);
}

