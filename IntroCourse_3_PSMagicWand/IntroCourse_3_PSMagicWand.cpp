/*==================================/
功能：全局魔术棒
依赖：opencv 2
时间：2015.5.6 Geekie Ong 
交流：http://Weibo.com/678260059
参考：OpenCV成长之路(3) Ronny
/==================================*/
#include "stdafx.h"
#include "ColorDetect.h"

CColorDetect psMagicWand;

void onMouse(int event, int x, int y, int flags, void* param)
{
	psMagicWand.on_mouse(event, x, y, flags, param);
}

int _tmain(int argc, _TCHAR* argv[])
{
	Mat image,imagecopy;//Mat是OpenCV里最基本的一个类，用来表示图像
	image = imread("../leah.jpg");
	if (image.empty())//判断图像是否读入
		return -1;
	image.copyTo(imagecopy);
	namedWindow("leah");
	namedWindow("MagicWand");
	imshow("leah", image);
	imshow("MagicWand", image);

	cvSetMouseCallback("leah", onMouse, &imagecopy);//自定义参数为图像
	waitKey(0);//显示图像
	cvDestroyAllWindows();
	return 0;
}

