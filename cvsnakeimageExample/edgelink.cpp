//http://blog.csdn.net/cxf7394373/article/details/8790844

#include "stdafx.h"
#include "highgui.h"
#include "cv.h"
#include "cxcore.h"

char wnd1[] = "in";
char wnd2[] = "out";
char wnd3[] = "Diff";

IplImage *pImg = NULL;    //Դͼ��
IplImage *pGray = NULL;   //�Ҷ�ͼ
IplImage *pCopy = NULL;
IplImage *pOut = NULL;    //��ֵͼ
IplImage *pDiff = NULL;		//�������ͼ

int inverse(IplImage *src);//�ص�����
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

	cvCopy(pGray,pCopy);//���ƶ�ֵͼ,ʹ��cvcopy����ͨ��һ�£������쳣

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

//��ֵͼȡ��
int inverse(IplImage *src)
{
	int height = src->height;                     // ͼ��߶� 
	int width = src->width;                       // ͼ���ȣ�����Ϊ��λ�� 
	int step = src->widthStep;                 // �����е�ͬ�е�֮����ֽ��� 
	int channels = src->nChannels;         // ��ɫͨ����Ŀ (1,2,3,4) 
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
//����ͼ���ж��ѵı�Ե
//��ĳһ��(i,j)Ϊ����,�������İ�����
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
			//��������ĵ�Ϊ255,�������İ�����
			//if (data[i * src->widthStep + j] == 255)
			if (data[i * src->widthStep + j] == 255)
			{
				int num = 0;
				for (int k = -1; k < 2; k++)
				{
					for (int l = -1; l < 2; l++)
					{
						//������������лҶ�ֵΪ0�ĵ㣬��ȥ�Ҹõ��ʮ������
						//if (k != 0 && l != 0 && data[(i + k) * src->widthStep + j + l] == 255)
						if (k != 0 && l != 0 && data[(i + k) * src->widthStep + j + l] == 255)
							num++;
					}
				}
				//�����������ֻ��һ������255��˵�������ĵ�Ϊ�˵㣬��������ʮ������
				if (num == 1)
				{
					for (int k = -2; k < 3; k++)
					{
						for (int l = -2; l < 3; l++)
						{
							//����õ��ʮ����������255�ĵ㣬��õ������ĵ�֮��ĵ���Ϊ255
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

