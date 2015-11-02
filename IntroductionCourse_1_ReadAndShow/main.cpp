#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
//core.hpp于OpenCV的一些基础数据结构相关;highgui.hpp和openCV的一些界面相关，如显示图像的窗口

int main()
{
	cv::Mat image;//Mat是OpenCV里最基本的一个类，它用来表示图像
	cv::Mat image0(240, 320, CV_8U, cv::Scalar(100));//创建了一个灰度图像，大小是320*240，图像上每个点的数据类型是无符号8位的，并用100填充所有像素点。 
	image = cv::imread("../leah.jpg");
	image.copyTo(image0);
	resize(image0, image0, cvSize(320, 240), 0, 0, CV_INTER_AREA);
	if (image.empty())//判断图像是否读入
		return -1;
	cv::namedWindow("leah"); 
	cv::namedWindow("leah0");
	
	cv::Mat newImage;
	newImage.create(image.size(), image.type());//创建一个跟原图像大小相同的空白图像
	
	cv::imshow("leah", image); //imshow是用来显示图像的函数
	cv::imshow("newImage", newImage);
	cv::imwrite("output.jpg",image0);//的第一个参数是写图像的路径，第二个参数是要写入的图像
	cv::waitKey(0);
	return 0;
}