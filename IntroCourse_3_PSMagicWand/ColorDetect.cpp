#include "stdafx.h"
#include "ColorDetect.h"
#include <iostream>

//cvtColor在opencv2/imgproc/imgproc.hpp头文件中定义

CColorDetect::CColorDetect()
{
}

CColorDetect::~CColorDetect()
{
}

void CColorDetect::SetTargetColor(uchar red, uchar green, uchar blue){
	target[0] = blue;
	target[1] = green;
	target[2] = red;
}

void CColorDetect::SetTargetColor(Vec3b color){
	target = color;
}

void CColorDetect::SetMinDistance(int dist){
	std::cout << "输入搜索半径:";
	std::cin >> dist;
	minDist = dist;
}


void CColorDetect::on_change(int position)//trackbar上调整的数字传给此函数，即为此函数的形参
{
	minDist = position;
	tempImage=process(tempImage);
	imshow("MagicWand", tempImage);
}

void CColorDetect::on_mouse(int event, int x, int y, int flags, void* param)
{
	// 显示参数实际数值
	printf("( %d, %d) ", x, y);
	printf("The Event is : %d ", event);//响应事件
	printf("The flags is : %d ", flags);//响应持续标记
	printf("The param is : %d\n", param);//用户定义的传递到cvSetMouseCallback函数调用的参数

	Mat image, imagedst;
	image = *(Mat*)param;
	bool mark = 0;

	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN:
		if (mark != 0)
		{
			target = image.at<cv::Vec3b>(y, x);//// 提取颜色,注意坐标顺序为(y,x)
		}
		else
		{
			mark++;
			target = image.at<cv::Vec3b>(y, x);
		}
		break;
	case CV_EVENT_LBUTTONUP:
		imagedst = process(image);//调用魔术棒处理函数
		imshow("MagicWand", imagedst);
		break;

	case CV_EVENT_RBUTTONUP:
		if (mark = 1)//为提取颜色则不做该操作。
		{
			tempImage = image;
			cvCreateTrackbar("MinDist", "leah", &minDist, 255, on_change);//创建滑动条（滑轨名，嵌入窗口名，滑轨关联参数，最大值（最小值为0），回调函数）
			on_change(minDist);
		}
		else
			break;
		break;
	}

}

Mat CColorDetect::process(const Mat& image)
{
	Mat ImageLab = image.clone();
	result.create(image.rows, image.cols, CV_8U);

	//将image转换为Lab格式存储在ImageLab中
	cvtColor(image, ImageLab, CV_BGR2Lab);
	//将目标颜色由BGR转换为Lab
	Mat temp(1, 1, CV_8UC3);
	temp.at<Vec3b>(0, 0) = target;//创建了一张1*1的临时图像并用目标颜色填充
	cvtColor(temp, temp, CV_BGR2Lab);
	target = temp.at<Vec3b>(0, 0);//再从临时图像的Lab格式中取出目标颜色

	// 创建处理用的迭代器
	Mat_<Vec3b>::iterator it = ImageLab.begin<Vec3b>();
	Mat_<Vec3b>::iterator itend = ImageLab.end<Vec3b>();
	Mat_<uchar>::iterator itout = result.begin<uchar>();
	while (it != itend)
	{
		//两个颜色值之间距离的计算
		int dist = static_cast<int>(norm<int, 3>(Vec3i((*it)[0] - target[0],
			(*it)[1] - target[1], (*it)[2] - target[2])));
		if (dist < minDist)
			(*itout) = 255;
		else
			(*itout) = 0;
		it++;
		itout++;
	}
	return result;
}
