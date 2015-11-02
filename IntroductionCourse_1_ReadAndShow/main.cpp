#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
//core.hpp��OpenCV��һЩ�������ݽṹ���;highgui.hpp��openCV��һЩ������أ�����ʾͼ��Ĵ���

int main()
{
	cv::Mat image;//Mat��OpenCV���������һ���࣬��������ʾͼ��
	cv::Mat image0(240, 320, CV_8U, cv::Scalar(100));//������һ���Ҷ�ͼ�񣬴�С��320*240��ͼ����ÿ����������������޷���8λ�ģ�����100����������ص㡣 
	image = cv::imread("../leah.jpg");
	image.copyTo(image0);
	resize(image0, image0, cvSize(320, 240), 0, 0, CV_INTER_AREA);
	if (image.empty())//�ж�ͼ���Ƿ����
		return -1;
	cv::namedWindow("leah"); 
	cv::namedWindow("leah0");
	
	cv::Mat newImage;
	newImage.create(image.size(), image.type());//����һ����ԭͼ���С��ͬ�Ŀհ�ͼ��
	
	cv::imshow("leah", image); //imshow��������ʾͼ��ĺ���
	cv::imshow("newImage", newImage);
	cv::imwrite("output.jpg",image0);//�ĵ�һ��������дͼ���·�����ڶ���������Ҫд���ͼ��
	cv::waitKey(0);
	return 0;
}