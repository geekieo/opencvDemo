/******************************************
参考：OpenCV成长之路(2)：图像的遍历
http://www.cnblogs.com/ronny/p/opencv_road_2.html
环境：vc12,opencv2.4.9
creater: Geekie 翁敬喻
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
	Mat image;//Mat是OpenCV里最基本的一个类，它用来表示图像
	Mat imagecopy1;
	imagecopy1.create(image.size(), image.type());//创建一个跟原图像大小相同的空白图像
	colorReduce colorreduce;
	image = imread("../leah.jpg");
	if (image.empty())//判断图像是否读入
		return -1;
	namedWindow("leah");
	imshow("leah", image); //imshow是用来显示图像的函数
	waitKey(1);//显示图像

	int flag;
	cout << "输入数字选择图像遍历方式" << endl << "1 Mat.at()函数遍历" << endl << "2 指针遍历" << endl << "3 Mat.isContinuous()函数遍历" << endl << "4 迭代器遍历" << endl << "请选择：";
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


	imwrite("../output.jpg", image);//的第一个参数是写图像的路径，第二个参数是要写入的图像
	waitKey(0);
	return 0;
}

