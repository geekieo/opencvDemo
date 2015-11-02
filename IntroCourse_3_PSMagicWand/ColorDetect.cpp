#include "stdafx.h"
#include "ColorDetect.h"
#include <iostream>

//cvtColor��opencv2/imgproc/imgproc.hppͷ�ļ��ж���

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
	std::cout << "���������뾶:";
	std::cin >> dist;
	minDist = dist;
}


void CColorDetect::on_change(int position)//trackbar�ϵ��������ִ����˺�������Ϊ�˺������β�
{
	minDist = position;
	tempImage=process(tempImage);
	imshow("MagicWand", tempImage);
}

void CColorDetect::on_mouse(int event, int x, int y, int flags, void* param)
{
	// ��ʾ����ʵ����ֵ
	printf("( %d, %d) ", x, y);
	printf("The Event is : %d ", event);//��Ӧ�¼�
	printf("The flags is : %d ", flags);//��Ӧ�������
	printf("The param is : %d\n", param);//�û�����Ĵ��ݵ�cvSetMouseCallback�������õĲ���

	Mat image, imagedst;
	image = *(Mat*)param;
	bool mark = 0;

	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN:
		if (mark != 0)
		{
			target = image.at<cv::Vec3b>(y, x);//// ��ȡ��ɫ,ע������˳��Ϊ(y,x)
		}
		else
		{
			mark++;
			target = image.at<cv::Vec3b>(y, x);
		}
		break;
	case CV_EVENT_LBUTTONUP:
		imagedst = process(image);//����ħ����������
		imshow("MagicWand", imagedst);
		break;

	case CV_EVENT_RBUTTONUP:
		if (mark = 1)//Ϊ��ȡ��ɫ�����ò�����
		{
			tempImage = image;
			cvCreateTrackbar("MinDist", "leah", &minDist, 255, on_change);//��������������������Ƕ�봰����������������������ֵ����СֵΪ0�����ص�������
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

	//��imageת��ΪLab��ʽ�洢��ImageLab��
	cvtColor(image, ImageLab, CV_BGR2Lab);
	//��Ŀ����ɫ��BGRת��ΪLab
	Mat temp(1, 1, CV_8UC3);
	temp.at<Vec3b>(0, 0) = target;//������һ��1*1����ʱͼ����Ŀ����ɫ���
	cvtColor(temp, temp, CV_BGR2Lab);
	target = temp.at<Vec3b>(0, 0);//�ٴ���ʱͼ���Lab��ʽ��ȡ��Ŀ����ɫ

	// ���������õĵ�����
	Mat_<Vec3b>::iterator it = ImageLab.begin<Vec3b>();
	Mat_<Vec3b>::iterator itend = ImageLab.end<Vec3b>();
	Mat_<uchar>::iterator itout = result.begin<uchar>();
	while (it != itend)
	{
		//������ɫֵ֮�����ļ���
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
