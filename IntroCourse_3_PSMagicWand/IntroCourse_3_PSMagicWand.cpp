/*==================================/
���ܣ�ȫ��ħ����
������opencv 2
ʱ�䣺2015.5.6 Geekie Ong 
������http://Weibo.com/678260059
�ο���OpenCV�ɳ�֮·(3) Ronny
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
	Mat image,imagecopy;//Mat��OpenCV���������һ���࣬������ʾͼ��
	image = imread("../leah.jpg");
	if (image.empty())//�ж�ͼ���Ƿ����
		return -1;
	image.copyTo(imagecopy);
	namedWindow("leah");
	namedWindow("MagicWand");
	imshow("leah", image);
	imshow("MagicWand", image);

	cvSetMouseCallback("leah", onMouse, &imagecopy);//�Զ������Ϊͼ��
	waitKey(0);//��ʾͼ��
	cvDestroyAllWindows();
	return 0;
}

