// FindRotation-angle.cpp : �������̨Ӧ�ó������ڵ㡣
//

// findContours.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"



#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp> 
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


#pragma comment(lib,"opencv_core2410d.lib")      
#pragma comment(lib,"opencv_highgui2410d.lib")      
#pragma comment(lib,"opencv_imgproc2410d.lib") 

#define PI 3.1415926

using namespace std;
using namespace cv;



int hough_line(Mat src)
{
	//��1������ԭʼͼ��Mat��������   
	Mat srcImage = src;//imread("1.jpg");  //����Ŀ¼��Ӧ����һ����Ϊ1.jpg���ز�ͼ
	Mat midImage, dstImage;//��ʱ������Ŀ��ͼ�Ķ���

	//��2�����б�Ե����ת��Ϊ�Ҷ�ͼ
	Canny(srcImage, midImage, 50, 200, 3);//����һ��canny��Ե���
	cvtColor(midImage, dstImage, CV_GRAY2BGR);//ת����Ե�����ͼΪ�Ҷ�ͼ

	//��3�����л����߱任
	vector<Vec4i> lines;//����һ��ʸ���ṹlines���ڴ�ŵõ����߶�ʸ������
	HoughLinesP(midImage, lines, 1, CV_PI / 180, 80, 50, 10);

	//��4��������ͼ�л��Ƴ�ÿ���߶�
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255), 1, CV_AA);
	}

	//��5����ʾԭʼͼ  
	imshow("��ԭʼͼ��1", srcImage);

	//��6����Ե�����ͼ 
	imshow("����Ե�����ͼ��2", midImage);

	//��7����ʾЧ��ͼ  
	imshow("��Ч��ͼ��3", dstImage);

	waitKey(0);  

	return 0;
}

int main()
{
	// Read input binary image

	char *image_name = "test.jpg";
	cv::Mat image = cv::imread(image_name, 0);
	if (!image.data)
		return 0;

	cv::namedWindow("Binary Image");
	cv::imshow("Binary Image", image);



	// ���ļ��м���ԭͼ ,�Ե�ͨ��ģʽ����
	IplImage *pSrcImage = cvLoadImage(image_name, CV_LOAD_IMAGE_GRAYSCALE);

	// תΪ2ֵͼ

	cvThreshold(pSrcImage, pSrcImage, 200, 255, cv::THRESH_BINARY_INV);


	image = cv::Mat(pSrcImage, true);

	cv::imwrite("binary.jpg", image);

	// Get the contours of the connected components
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(image,
		contours, // a vector of contours 
		CV_RETR_EXTERNAL, // retrieve the external contours
		CV_CHAIN_APPROX_NONE); // retrieve all pixels of each contours

	// Print contours' length
	std::cout << "Contours: " << contours.size() << std::endl;
	std::vector<std::vector<cv::Point>>::const_iterator itContours = contours.begin();
	for (; itContours != contours.end(); ++itContours)
	{

		std::cout << "Size: " << itContours->size() << std::endl;
	}

	// draw black contours on white image
	cv::Mat result(image.size(), CV_8U, cv::Scalar(255));
	cv::drawContours(result, contours,
		-1, // draw all contours
		cv::Scalar(0), // in black
		2); // with a thickness of 2

	cv::namedWindow("Contours");
	cv::imshow("Contours", result);






	// Eliminate too short or too long contours
	int cmin = 100;  // minimum contour length
	int cmax = 1000; // maximum contour length
	std::vector<std::vector<cv::Point>>::const_iterator itc = contours.begin();
	while (itc != contours.end()) {

		if (itc->size() < cmin || itc->size() > cmax)
			itc = contours.erase(itc);
		else
			++itc;
	}

	// draw contours on the original image
	cv::Mat original = cv::imread(image_name);
	cv::drawContours(original, contours,
		-1, // draw all contours
		cv::Scalar(255, 255, 0), // in white
		2); // with a thickness of 2

	cv::namedWindow("Contours on original");
	cv::imshow("Contours on original", original);



	// Let's now draw black contours on white image
	result.setTo(cv::Scalar(255));
	cv::drawContours(result, contours,
		-1, // draw all contours
		cv::Scalar(0), // in black
		1); // with a thickness of 1
	image = cv::imread("binary.jpg", 0);

	//imshow("lll",result);
	//waitKey(0);

	// testing the bounding box 
	//////////////////////////////////////////////////////////////////////////////
	//����任����ֱ�߼�⣬�˴�ʹ�õ���probabilistic Hough transform��cv::HoughLinesP��������standard Hough transform��cv::HoughLines��

	cv::Mat result_line(image.size(), CV_8U, cv::Scalar(255));
	result_line = result.clone();

	hough_line(result_line);

	//Mat tempimage;

	//��2�����б�Ե����ת��Ϊ�Ҷ�ͼ
	//Canny(result_line, tempimage, 50, 200, 3);//����һ��canny��Ե���
	//imshow("canny",tempimage);
	//waitKey(0);

	//cvtColor(tempimage,result_line, CV_GRAY2BGR);//ת����Ե�����ͼΪ�Ҷ�ͼ
	vector<Vec4i> lines;

	cv::HoughLinesP(result_line, lines, 1, CV_PI / 180, 80, 50, 10);

	for (int i = 0; i < lines.size(); i++)
	{
		line(result_line, cv::Point(lines[i][0], lines[i][1]), cv::Point(lines[i][2], lines[i][3]), Scalar(0, 0, 0), 2, 8, 0);
	}
	cv::namedWindow("line");
	cv::imshow("line", result_line);
	waitKey(0);

	/////////////////////////////////////////////////////////////////////////////////////////////
	//

	//std::vector<std::vector<cv::Point>>::const_iterator itc_rec= contours.begin();
	//while (itc_rec!=contours.end())
	//{
	//	cv::Rect r0= cv::boundingRect(cv::Mat(*(itc_rec)));
	//	cv::rectangle(result,r0,cv::Scalar(0),2);
	//		++itc_rec;
	//}



	//cv::namedWindow("Some Shape descriptors");
	//cv::imshow("Some Shape descriptors",result);


	CvBox2D     End_Rage2D;
	CvPoint2D32f rectpoint[4];
	CvMemStorage *storage = cvCreateMemStorage(0);  //�����ڴ�ռ�


	CvSeq*      contour = NULL;     //CvSeq���� ��ż�⵽��ͼ��������Ե���е�����ֵ������ֵ�����Ľṹ����������ʽ

	cvFindContours(pSrcImage, storage, &contour, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);//�⺯����ѡ�������в���



	for (; contour; contour = contour->h_next)   //���contour��Ϊ�գ���ʾ�ҵ�һ����������������д��ֻ��ʾһ������
		//���Ϊfor(; contour; contour = contour->h_next) �Ϳ���ͬʱ��ʾ�������
	{

		End_Rage2D = cvMinAreaRect2(contour);
		//����cvMinAreaRect2��������õ���С��Χ����  �����ѵó���������ĽǶȣ����,�߶ȣ����е����������CvBox2D���͵Ľṹ���У�
		//��Ҫ��������������
		for (int i = 0; i< 4; i++)
		{
			//CvArr* s=(CvArr*)&result;
			//cvLine(s,cvPointFrom32f(rectpoint[i]),cvPointFrom32f(rectpoint[(i+1)%4]),CV_G(0,0,255),2);
			line(result, cvPointFrom32f(rectpoint[i]), cvPointFrom32f(rectpoint[(i + 1) % 4]), Scalar(125), 2);
		}
		cvBoxPoints(End_Rage2D, rectpoint);

		std::cout << " angle:\n" << (float)End_Rage2D.angle << std::endl;      //����������ת�Ƕ� 

	}
	cv::imshow("lalalal", result);
	cv::waitKey();
	return 0;


}