// BatchProcess.cpp : �������̨Ӧ�ó������ڵ㡣
//

// SHIYAN.cpp : Defines the entry point for the console application.
//
#include"stdlib.h"   //system��Ҫ�������
#include "stdafx.h"
#include <highgui.h>
#include "stdio.h"  
#include "cv.h"  

using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	int image_id = 1;
	char filename[256];
	char filename2[256];

	char winname[256];
	IplImage *image = 0, *imageresize = 0;
	sprintf(filename, "D:\\ѵ��ͼƬ��\\%d.jpg", image_id);
	IplImage* src = cvLoadImage(filename);
	cout << "\n ��ʼ��һ���� \n";

	while (src)
	{

		sprintf(winname, "%d.jpg", image_id);
		imageresize = cvCreateImage(cvSize(60, 60), IPL_DEPTH_8U, 3);  //����ͷ����������
		cvResize(src, imageresize, CV_INTER_LINEAR);  //����cvResize ���µ���ͼ��src��������ROI����ʹ����ȷƥ��Ŀ��dst������ROI����
		sprintf(filename2, "%d.jpg", image_id);
		cvSaveImage(filename2, imageresize);
		cvReleaseImage(&imageresize);

		cvReleaseImage(&src);
		image_id++;
		sprintf(filename, "D:\\00000\\%d.bmp", image_id);
		src = cvLoadImage(filename);
	}


	cout << "\n ��һ����ϣ� \n";
	system("PAUSE");
}
