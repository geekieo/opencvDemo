#pragma once
#include"cv.h"
#include"highgui.h"
using namespace cv;

class CColorDetect
{
public:
	CColorDetect();
	~CColorDetect();

public:
	void SetMinDistance(int dist);
	void SetTargetColor(uchar red, uchar green, uchar blue);
	void SetTargetColor(Vec3b color); //set the target color
	void on_change(int position);//当trackbar位置被改变的时，系统会调用这个回调函数，并将参数pos设置为表示trackbar位置的数值。
	void on_mouse(int event, int x, int y, int flags, void*);//鼠标响应 setMouseCalback 的回调函数
	Mat process(const Mat& image); //main process;主处理程序，
private:
	Mat srcImage;
	Mat tempImage;
	int minDist=50; //minium acceptable distance,用于限定两种颜色之间的距离，相当于PhotoShop中魔术棒工具的阈值
	Vec3b target;//target color;目标颜色，相当于种子颜色,通道顺序为BGR
	Mat result; //the result;存储处理得到的结果图像
};

