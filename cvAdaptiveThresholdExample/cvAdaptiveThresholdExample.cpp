// cvAdaptiveThresholdExample.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


/************cvAdaptiveThreshold Example************/

#include "highgui.h"
#include "cv.h"
#include <stdlib.h>
#include <stdio.h>

char wnd1[] = "in";
char wnd2[] = "out";

//��ȡtrackbar�ϵ�����ֵ,ʵ��������������on_track��
int _blocksize = 0;
int _param1 = 0;

IplImage *pImg = NULL;    //Դͼ��
IplImage *pGray = NULL;   //�Ҷ�ͼ
IplImage *pOut = NULL;    //��ֵͼ������

void on_track(int position);  //trackbar�ص�����

int main(int argc, char **argv)
{
	cvNamedWindow(wnd1, 1);
	cvNamedWindow(wnd2, 1);

	pImg = cvLoadImage("4ul2.bmp");
	pGray = cvCreateImage(cvGetSize(pImg), IPL_DEPTH_8U, 1);
	pOut = cvCreateImage(cvGetSize(pImg), IPL_DEPTH_8U, 1);
	cvCvtColor(pImg, pGray, CV_RGB2GRAY);

	//��������������
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
	int blocksize = _blocksize * 2 + 3;     //������ֵ�����������С3,5,7...
	int param1 = _param1 - 50;    //����ֵ�ͼ�Ȩ��ֵ��ȥ�ĳ���, ��Χȡ[-50,50]

	cvAdaptiveThreshold(pGray,
		pOut,
		255,
		CV_ADAPTIVE_THRESH_MEAN_C,
		CV_THRESH_BINARY, blocksize, param1
		);
	printf("blocksize: %d, param1: %d\n", blocksize, param1);
	cvShowImage(wnd2, pOut);
}

