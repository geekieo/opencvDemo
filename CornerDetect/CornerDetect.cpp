// CornerDetect.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "cv.h"
using namespace cv;
using namespace std;

/// Global variables
Mat src, src_gray;
int thresh = 100;
int max_thresh = 255;

char* source_window = "Source image";
char* corners_window = "Corners detected";

/// Function header
void cornerHarris_demo(int, void*);

/** @function main */
int main(int argc, char** argv)
{
	Mat src = imread("D:\\[Experiment]\\口罩图像\\pylon_2ed\\quemianjin\\12.tiff", 1); //读图
	if (!src.data)
	{
		std::cout << "Fail to load image" << std::endl;
		return 0;
	}
	Mat srcGray;
	cvtColor(src, srcGray, CV_BGR2GRAY);
	IplImage *g_pGrayImage = (&(IplImage)srcGray);
	IplImage *g_pBinaryImage = cvCreateImage(cvGetSize(g_pGrayImage), IPL_DEPTH_8U, 1);//创建单通道灰度图
	cvThreshold(g_pGrayImage, g_pBinaryImage, 0, 255, CV_THRESH_OTSU);//二值化
	Mat srcBinary(g_pBinaryImage, false);

	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(20, 20));
	Mat out_gray;
	//blur(srcBinary, out_gray, cv::Size(3, 3));//模糊
	dilate(srcBinary, out_gray, element);//膨胀
	erode(out_gray, out_gray, element);//腐蚀
	src_gray = out_gray;
	imshow("outgray", out_gray);
	/// Load source image and convert it to gray74+++++++
	//src = imread("corner.png", 1);
	//cvtColor(src, src_gray, CV_BGR2GRAY);

	/// Create a window and a trackbar
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	createTrackbar("Threshold: ", source_window, &thresh, max_thresh, cornerHarris_demo);
	imshow(source_window, src);

	cornerHarris_demo(0, 0);

	waitKey(0);
	return(0);
}

/** @function cornerHarris_demo */
void cornerHarris_demo(int, void*)
{

	Mat dst, dst_norm, dst_norm_scaled;
	dst = Mat::zeros(src.size(), CV_32FC1);

	/// Detector parameters
	int blockSize = 30;
	int apertureSize = 5;
	double k = 0.04;

	/// Detecting corners
	cornerHarris(src_gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT);

	/// Normalizing
	normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(dst_norm, dst_norm_scaled);

	/// Drawing a circle around corners
	for (int j = 0; j < dst_norm.rows; j++)
	{
		for (int i = 0; i < dst_norm.cols; i++)
		{
			if ((int)dst_norm.at<float>(j, i) > thresh)
			{
				circle(dst_norm_scaled, Point(i, j), 5, Scalar(0), 2, 8, 0);
			}
		}
	}
	/// Showing the result
	namedWindow(corners_window, CV_WINDOW_AUTOSIZE);
	imshow(corners_window, dst_norm_scaled);
}


