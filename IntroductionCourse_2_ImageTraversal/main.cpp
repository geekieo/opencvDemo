/******************************************
�ο���OpenCV�ɳ�֮·(2)��ͼ��ı���
http://www.cnblogs.com/ronny/p/opencv_road_2.html
������vc12,opencv2.4.9
creater: Geekie �̾���
*******************************************/

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "colorReduce.h"
#include <iostream>
using namespace cv;
using namespace std;


int main()
{
	Mat image;//Mat��OpenCV���������һ���࣬��������ʾͼ��
	Mat imagecopy1;
	imagecopy1.create(image.size(), image.type());//����һ����ԭͼ���С��ͬ�Ŀհ�ͼ��
	colorReduce colorreduce;
	image = imread("../leah.jpg");
	if (image.empty())//�ж�ͼ���Ƿ����
		return -1;
	namedWindow("leah");
	imshow("leah", image); //imshow��������ʾͼ��ĺ���
	waitKey(1);//��ʾͼ��

	int flag;
	cout << "��������ѡ��ͼ�������ʽ" << endl << "1 Mat.at()��������" << endl << "2 ָ�����" << endl << "3 Mat.isContinuous()��������" << endl << "4 ����������" << endl << "��ѡ��";
	cin >> flag;
	switch (flag)
	{
	case 1:
		colorreduce.cr_at(image, 64);
		break;
	case 2:
		colorreduce.cr_point(image, imagecopy1, 64);
		break; 
	case 3:
		colorreduce.cr_isContinuous(image, imagecopy1, 64);
		break;
	case 4:
		colorreduce.cr_iterator(image, imagecopy1, 64);
		break;
	}


	namedWindow("output");
	imshow("output", imagecopy1);


	imwrite("../output.jpg", image);//�ĵ�һ��������дͼ���·�����ڶ���������Ҫд���ͼ��
	waitKey(0);
	return 0;
}

