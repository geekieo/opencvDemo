// BatchProcess.cpp : 定义控制台应用程序的入口点。
//

// SHIYAN.cpp : Defines the entry point for the console application.
//
#include"stdlib.h"   //system需要调用这个
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
	sprintf(filename, "D:\\训练图片库\\%d.jpg", image_id);
	IplImage* src = cvLoadImage(filename);
	cout << "\n 开始归一化！ \n";

	while (src)
	{

		sprintf(winname, "%d.jpg", image_id);
		imageresize = cvCreateImage(cvSize(60, 60), IPL_DEPTH_8U, 3);  //创建头并分配数据
		cvResize(src, imageresize, CV_INTER_LINEAR);  //函数cvResize 重新调整图像src（或它的ROI），使它精确匹配目标dst（或其ROI）。
		sprintf(filename2, "%d.jpg", image_id);
		cvSaveImage(filename2, imageresize);
		cvReleaseImage(&imageresize);

		cvReleaseImage(&src);
		image_id++;
		sprintf(filename, "D:\\00000\\%d.bmp", image_id);
		src = cvLoadImage(filename);
	}


	cout << "\n 归一化完毕！ \n";
	system("PAUSE");
}
