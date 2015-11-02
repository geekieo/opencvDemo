//http://blog.csdn.net/cxf7394373/article/details/8790844

#include "stdafx.h"
#include "highgui.h"
#include "cv.h"
#include "cxcore.h"

char wnd1[] = "in";
char wnd2[] = "out";
char wnd3[] = "Diff";

IplImage *pImg = NULL;    //源图像
IplImage *pGray = NULL;   //灰度图
IplImage *pCopy = NULL;
IplImage *pOut = NULL;    //二值图
IplImage *pDiff = NULL;		//相减差异图

int inverse(IplImage *src);//回调函数
int ConnectEdge(IplImage * src);

int main(int argc, char **argv)
{
	cvNamedWindow(wnd1, 1);
	cvNamedWindow(wnd2, 1);
	cvNamedWindow(wnd3, 1);
	pImg = cvLoadImage("D:\\Documents\\Visual Studio 2013\\Projects\\opencvDemo\\cvAdaptiveThresholdExample\\blocksize1-param70.bmp");
	CvSize cvsize = cvGetSize(pImg);
	pGray = cvCreateImage(cvsize, IPL_DEPTH_8U, 1);
	pCopy = cvCreateImage(cvsize, IPL_DEPTH_8U, 1);
	pOut = cvCreateImage(cvsize, IPL_DEPTH_8U, 1);
	pDiff = cvCreateImage(cvsize, IPL_DEPTH_8U, 1);
	cvCvtColor(pImg, pGray, CV_RGB2GRAY);

	cvCopy(pGray,pCopy);//复制二值图,使用cvcopy必须通道一致，否则报异常

	inverse(pGray);
	ConnectEdge(pCopy);

	cvAbsDiff(pCopy, pGray, pDiff);

	cvShowImage(wnd1, pImg);
	cvShowImage(wnd2, pGray);
	cvShowImage(wnd3, pDiff);

	cvWaitKey(0);

	cvReleaseImage(&pImg);
	cvReleaseImage(&pOut);
	cvReleaseImage(&pGray);
	cvDestroyWindow(wnd1);
	cvDestroyWindow(wnd2);
	cvDestroyWindow(wnd3);

	return 0;
}

//二值图取反
int inverse(IplImage *src)
{
	int height = src->height;                     // 图像高度 
	int width = src->width;                       // 图像宽度（像素为单位） 
	int step = src->widthStep;                 // 相邻行的同列点之间的字节数 
	int channels = src->nChannels;         // 颜色通道数目 (1,2,3,4) 
	uchar *data = (uchar *)src->imageData;
	for (int i = 0; i != height; ++i)
	{
		for (int j = 0; j != width; ++j)
		{
			for (int k = 0; k != channels; ++k)
			{
				data[i*step + j*channels + k] = 255 - data[i*step + j*channels + k];
			}
		}
	}
	pGray = src;
	return 0;
}
//////////////////////////////////////////////////////////////////////////
//连接图像中断裂的边缘
//以某一点(i,j)为中心,分析它的八邻域
//////////////////////////////////////////////////////////////////////////
int ConnectEdge(IplImage * src)
{
	if (NULL == src)
		return 1;

	int width = src->width;
	int height = src->height;

	uchar * data = (uchar *)src->imageData;
	for (int i = 2; i < height - 2; i++)
	{
		for (int j = 2; j < width - 2; j++)
		{
			//如果该中心点为255,则考虑它的八邻域
			//if (data[i * src->widthStep + j] == 255)
			if (data[i * src->widthStep + j] == 255)
			{
				int num = 0;
				for (int k = -1; k < 2; k++)
				{
					for (int l = -1; l < 2; l++)
					{
						//如果八邻域中有灰度值为0的点，则去找该点的十六邻域
						//if (k != 0 && l != 0 && data[(i + k) * src->widthStep + j + l] == 255)
						if (k != 0 && l != 0 && data[(i + k) * src->widthStep + j + l] == 255)
							num++;
					}
				}
				//如果八邻域中只有一个点是255，说明该中心点为端点，则考虑他的十六邻域
				if (num == 1)
				{
					for (int k = -2; k < 3; k++)
					{
						for (int l = -2; l < 3; l++)
						{
							//如果该点的十六邻域中有255的点，则该点与中心点之间的点置为255
							//if (!(k < 2 && k > -2 && l < 2 && l > -2) && data[(i + k) * src->widthStep + j + l] == 255)
							if (!(k < 2 && k > -2 && l < 2 && l > -2) && data[(i + k) * src->widthStep + j + l] == 255)
							{
								//data[(i + k / 2) * src->widthStep + j + l / 2] = 255;
								data[(i + k / 2) * src->widthStep + j + l / 2] = 255;
							}
						}
					}
				}
			}
		}
	}
}

